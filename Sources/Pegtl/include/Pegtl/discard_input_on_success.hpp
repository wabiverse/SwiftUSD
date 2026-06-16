// Copyright (c) 2019-2022 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef PXR_PEGTL_DISCARD_INPUT_ON_SUCCESS_HPP
#define PXR_PEGTL_DISCARD_INPUT_ON_SUCCESS_HPP

#include <Pegtl/apply_mode.hpp>
#include <Pegtl/config.hpp>
#include <Pegtl/match.hpp>
#include <Pegtl/nothing.hpp>
#include <Pegtl/rewind_mode.hpp>

namespace PXR_PEGTL_NAMESPACE
{
   struct discard_input_on_success
      : maybe_nothing
   {
      template< typename Rule,
                apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      {
         const bool result = PXR_PEGTL_NAMESPACE::match< Rule, A, M, Action, Control >( in, st... );
         if( result ) {
            in.discard();
         }
         return result;
      }
   };

}  // namespace PXR_PEGTL_NAMESPACE

#endif
