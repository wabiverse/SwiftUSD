// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef PXR_PEGTL_HPP
#define PXR_PEGTL_HPP

#include "Pegtl/config.hpp"
#include "Pegtl/demangle.hpp"
#include "Pegtl/parse.hpp"
#include "Pegtl/version.hpp"

#include "Pegtl/ascii.hpp"
#include "Pegtl/rules.hpp"
#include "Pegtl/utf8.hpp"

#include "Pegtl/argv_input.hpp"
#include "Pegtl/buffer_input.hpp"
#include "Pegtl/cstream_input.hpp"
#include "Pegtl/istream_input.hpp"
#include "Pegtl/memory_input.hpp"
#include "Pegtl/read_input.hpp"
#include "Pegtl/string_input.hpp"

// This has to be included *after* the above inputs,
// otherwise the amalgamated header will not work!
#include "Pegtl/file_input.hpp"

#include "Pegtl/change_action.hpp"
#include "Pegtl/change_action_and_state.hpp"
#include "Pegtl/change_action_and_states.hpp"
#include "Pegtl/change_control.hpp"
#include "Pegtl/change_state.hpp"
#include "Pegtl/change_states.hpp"

#include "Pegtl/disable_action.hpp"
#include "Pegtl/enable_action.hpp"

#include "Pegtl/discard_input.hpp"
#include "Pegtl/discard_input_on_failure.hpp"
#include "Pegtl/discard_input_on_success.hpp"

#include "Pegtl/visit.hpp"

#if defined( __cpp_exceptions )
#include "Pegtl/must_if.hpp"
#endif

#endif
