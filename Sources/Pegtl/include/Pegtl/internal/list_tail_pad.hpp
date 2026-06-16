// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef PXR_PEGTL_INTERNAL_LIST_TAIL_PAD_HPP
#define PXR_PEGTL_INTERNAL_LIST_TAIL_PAD_HPP

#include "../config.hpp"

#include <Pegtl/internal/list.hpp>
#include <Pegtl/internal/opt.hpp>
#include <Pegtl/internal/pad.hpp>
#include <Pegtl/internal/seq.hpp>
#include <Pegtl/internal/star.hpp>

namespace PXR_PEGTL_NAMESPACE::internal
{
   template< typename Rule, typename Sep, typename Pad >
   using list_tail_pad = seq< Rule, star< pad< Sep, Pad >, Rule >, opt< star< Pad >, Sep > >;

}  // namespace PXR_PEGTL_NAMESPACE::internal

#endif
