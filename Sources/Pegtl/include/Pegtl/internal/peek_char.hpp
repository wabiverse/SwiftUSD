// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef PXR_PEGTL_INTERNAL_PEEK_CHAR_HPP
#define PXR_PEGTL_INTERNAL_PEEK_CHAR_HPP

#include <cstddef>

#include "../config.hpp"

#include "input_pair.hpp"

namespace PXR_PEGTL_NAMESPACE::internal
{
   struct peek_char
   {
      using data_t = char;
      using pair_t = input_pair< char >;

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in ) noexcept( noexcept( in.empty() ) )
      {
         if( in.empty() ) {
            return { 0, 0 };
         }
         return { in.peek_char(), 1 };
      }
   };

}  // namespace PXR_PEGTL_NAMESPACE::internal

#endif
