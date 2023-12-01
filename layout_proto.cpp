#include <iostream>
#include <string>
#include <cstdint>

/**
** @brief Testing ground for layout creation
** The goal is to be able to create layouts with expressions like
** \code
** auto myLayout = {
**    {SplashComponent(background_image)},
**    {{80, 10}, TextComponent("Yo")},
**    {{5, 30}, SliderComponent(10,2,10)},
** };
** \endcode
** which act as templates for windows. Windows are created in arduino setup() through WindowManager
** \code
** Window myWindow = windowmanager.createWindow(MAIN_MENU, myLayout);
** \endcode
*/

using std::size_t;
using std::string;
struct Point { int x; int y; };

class Component {
        public:
                virtual const char* getName() = 0;
};

class SliderComponent : public Component{
        public:
                const char* getName() override {return "Slider";}
                SliderComponent(int val) : _val(val) {}
        private:
                int _val;
};

class TextComponent : public Component{
        public:
                const char* getName() override {return "Text";}
                TextComponent(string const& label) : _str(label) {}
        private:
                string _str;
};

template <typename _Component>
struct WindowedComponent {
        WindowedComponent(Point const& pos,_Component const& cmp) : position(pos), component(cmp) {}
        Point position;
        _Component component;
};

template <typename... _WComponents>
struct Layout;


//base
template <typename _Component>
struct Layout<_Component> {
        Layout(WindowedComponent<_Component> const& comp) : head(comp) {}

        // template <size_t N>
        // auto  getComponent() const {
        //         static_assert(N == 0, "WROOOOOOOOONG");
        //         return head;
        // }

        WindowedComponent<_Component> head;
};

//recurse
template <typename _First, typename... _Rest>
struct Layout<_First, _Rest...> {
        WindowedComponent<_First> head;
        Layout<_Rest...> tail;

        Layout(WindowedComponent<_First> const& head, WindowedComponent<_Rest> const&... rest) : head(head), tail(Layout<_Rest...>(rest...)) {}
        // Layout(Layout<_Rest...> const& other) {}

        template <size_t N>
        auto getComponent() const {
                if (N == 0) {
                        return head;
                } else {
                        return tail.template getComponent<N-1>();
                }
        }
};

template <typename _Layout, size_t N>
struct LayoutComponentAt;

template <typename _First, typename... _Rest>
struct LayoutComponentAt<Layout<_First, _Rest...>, 0> {
        auto get(Layout<_First, _Rest...> const& layout) {
                return layout.head;
        }
};

template <typename _First, typename... _Rest, size_t N>
struct LayoutComponentAt<Layout<_First, _Rest...>, N> {
        auto get(Layout<_First, _Rest...> const& layout) {
                return LayoutComponentAt<Layout<_Rest...>, N-1>().get(layout.tail);
        }
};

// template <typename _Layout>
// void printSingleLayout(_Layout const& layout);

// template <typename _Component>
// void printSingleLayout(Layout<_Component> const& layout) {
//         using Cmp = WindowedComponent<_Component>;
//         std::cout << layout.getComponent<0>().component.getName() << std::endl;
// }

auto layout = Layout<TextComponent, SliderComponent>(
        WindowedComponent<TextComponent>{{3,20}, TextComponent("Hi")},
        WindowedComponent<SliderComponent>{{3,20}, SliderComponent(0)}
);

int main() {
        auto myComp = WindowedComponent<TextComponent>{{3,20}, TextComponent("Hi")};
        std::cout << LayoutComponentAt<decltype(layout), 0>().get(layout).component.getName() << std::endl;
        std::cout << LayoutComponentAt<decltype(layout), 1>().get(layout).component.getName() << std::endl;

        return 0;
}

// template <size_t N, typename... _Component>
// struct Layout;

// template <typename... _Component>
// struct Layout<0, _Component...> {};

// template <std::size_t N, typename... _Components>
// struct Layout<N, TypeList<_Components...>> {
//         using ComponentType = typename TypeAtIndex<TypeList<_Components...>, N>::type;
//         WindowedComponent<ComponentType> head;
//         Layout<N-1, TailTypeList<_Components...>> rest;
// };

// template <typename... Components>
// auto makeLayout(WindowedComponent<Components>&&... components) {
//     return Layout<sizeof...(Components), std::decay_t<WindowedComponent<Components>>...>{std::forward<WindowedComponent<Components>>(components)...};
// }

// template <typename... Types>
// struct TypeList {};

// template <typename TypeList>
// struct TailTypeList;

// template <typename Head, typename... Tail>
// struct TailTypeList<TypeList<Head, Tail...>> {
//     using type = TypeList<Tail...>;
// };

// template <typename TypeList, std::size_t Index>
// struct TypeAtIndex;

// template <typename Head, typename... Tail>
// struct TypeAtIndex<TypeList<Head, Tail...>, 0> {
//     using type = Head;
// };

// template <typename Head, typename... Tail, std::size_t Index>
// struct TypeAtIndex<TypeList<Head, Tail...>, Index> {
//     using type = typename TypeAtIndex<TypeList<Tail...>, Index - 1>::type;
// };
