// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Copyright (c) 2009-2013 Illumina, Inc.
//
// This software is provided under the terms and conditions of the
// Illumina Open Source Software License 1.
//
// You should have received a copy of the Illumina Open Source
// Software License 1 along with this program. If not, see
// <https://github.com/sequencing/licenses/>
//

/// \file

/// \author Chris Saunders
///
#include "blt_util/depth_stream_stat.hh"

#include <iostream>



std::ostream&
operator<<(std::ostream& os,const depth_stream_stat& ss) {

    os << "sample_size: " << ss.sample_size() << " nonzero: " << ss.nonzero() << " min: " << ss.min() << " max: " << ss.max()
       << " mean: " << ss.mean() << " sd: " << ss.sd();

    return os;
}
