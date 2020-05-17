TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        core/algo.cpp \
        core/random.cpp \
        direction/direction.cpp \
        game/action.cpp \
        game/avatar.cpp \
        game/exploration/accessibility_test.cpp \
        game/exploration/mark.cpp \
        game/exploration/mark_grid.cpp \
        game/exploration/pacman_exploration_rules.cpp \
        game/game.cpp \
        game/opponent.cpp \
        game/pacman.cpp \
        game/pacman_type.cpp \
        game/player.cpp \
        game/square.cpp \
        game/turn_info.cpp \
        game/world.cpp \
        grid/exploration/spread_exploration.cpp \
        grid/grid_algo.cpp \
        grid/grid_base.cpp \
        main.cpp \
        test/spread_exploration/old_compilation_test.cpp \
        test/spread_exploration/spread_exploration_tests.cpp \
        vec2/vec2i.cpp \
        vec2/vec2u.cpp

HEADERS += \
    core/algo.hpp \
    core/default_arg.hpp \
    core/random.hpp \
    direction/direction.hpp \
    direction/neighbourhood.hpp \
    game/action.hpp \
    game/avatar.hpp \
    game/exploration/accessibility_test.hpp \
    game/exploration/associative_functor.hpp \
    game/exploration/mark.hpp \
    game/exploration/mark_grid.hpp \
    game/exploration/pacman_exploration.hpp \
    game/exploration/pacman_exploration_rules.hpp \
    game/game.hpp \
    game/opponent.hpp \
    game/pacman.hpp \
    game/pacman_type.hpp \
    game/player.hpp \
    game/square.hpp \
    game/turn_info.hpp \
    game/world.hpp \
    grid/exploration/direction_to.hpp \
    grid/exploration/exploration_rules/decorator/torus.hpp \
    grid/exploration/exploration_rules/directions4_exploration_rules.hpp \
    grid/exploration/exploration_rules/torus_directions4_exploration_rules.hpp \
    grid/exploration/mark.hpp \
    grid/exploration/mark_grid.hpp \
    grid/exploration/reachable_positions.hpp \
    grid/exploration/reachable_squares.hpp \
    grid/exploration/spread_exploration.hpp \
    grid/exploration/stop_condition/first_square_found.hpp \
    grid/exploration/stop_condition/no_stop_condition.hpp \
    grid/exploration/stop_condition/positions_treated.hpp \
    grid/grid.hpp \
    grid/grid_algo.hpp \
    grid/grid_base.hpp \
    grid/grid_iterator.hpp \
    grid/grid_types.hpp \
    grid/grid_view.hpp \
    grid/iterator_range.hpp \
    grid/neighbourhood.hpp \
    log/log.hpp \
    test/spread_exploration/old_compilation_test.hpp \
    test/spread_exploration/spread_exploration_tests.hpp \
    vec2/vec2i.hpp \
    vec2/vec2u.hpp \
    version.hpp

DISTFILES += \
    catlist.txt \
    todo.txt
