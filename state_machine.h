#pragma once

#include <iostream>

#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>

#include <boost/mpl/list.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

// Use forward declaration in order to declarate our FSM before initial state
// Good practive to have all states pre-declarated somethere
struct off_state;
struct on_state;
struct active_state;

// State Machine:
struct state_machine : sc::state_machine<state_machine, off_state> {};

//Events
struct turn_off : sc::event< turn_off > {};
struct turn_on  : sc::event< turn_on > {};
struct start    : sc::event< start > {};
struct finish   : sc::event< finish > {};

/**
 * Some template magic to merge common reactions for all states and derived
 * @tparam base_transitions - list of reactions to be common for all states
 */

template<class ...base_transitions>
struct transitions_list : mpl::list<base_transitions...> {
    template <class ...derived_transitions>
    using merge = transitions_list<base_transitions..., derived_transitions...>;
};

typedef transitions_list<sc::transition<turn_off, off_state>> base_transtions;

// States:
struct off_state : sc::simple_state<off_state, state_machine> {
  off_state () { std::cout << "In OFF state" << std::endl; }
  typedef mpl::list< sc::transition<turn_on, on_state>> reactions;
};

struct on_state : sc::simple_state<on_state, state_machine> {
  on_state () { std::cout << "In ON state" << std::endl; }
  typedef base_transtions::merge< sc::transition<start, active_state> > reactions; 
};

struct active_state : sc::simple_state<active_state, state_machine> {
  active_state () { std::cout << "In ACTIVE state" << std::endl; }
  typedef base_transtions::merge< sc::transition<finish, on_state> > reactions;
};