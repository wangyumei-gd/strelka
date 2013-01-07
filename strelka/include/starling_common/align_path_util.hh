// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Copyright (c) 2009-2012 Illumina, Inc.
//
// This software is covered by the "Illumina Genome Analyzer Software
// License Agreement" and the "Illumina Source Code License Agreement",
// and certain third party copyright/licenses, and any user of this
// source file is bound by the terms therein (see accompanying files
// Illumina_Genome_Analyzer_Software_License_Agreement.pdf and
// Illumina_Source_Code_License_Agreement.pdf and third party
// copyright/license notices).
//
//

/// \file
///
/// \author Chris Saunders
///

#ifndef __ALIGN_PATH_UTIL_HH
#define __ALIGN_PATH_UTIL_HH

#include "starling_common/align_path.hh"
#include "blt_util/blt_types.hh"
#include "starling_common/starling_types.hh"


#include <cassert>


namespace ALIGNPATH {

    inline
    void
    increment_path(const path_t& path,
                   unsigned& path_index,
                   unsigned& read_offset,
                   pos_t& ref_offset)
    {
        const path_segment& ps(path[path_index]);
        
        if       (ps.type == MATCH) {
            read_offset += ps.length;
            ref_offset += ps.length;
        } else if(ps.type == DELETE || ps.type == SKIP){
            ref_offset += ps.length;
        } else if(ps.type == INSERT || ps.type == SOFT_CLIP){
            read_offset += ps.length;
        } else if(ps.type == HARD_CLIP || ps.type == PAD){
            // do nothing
        } else {
            assert(0); // can't handle other CIGAR types yet
        }
        
        path_index++;
    }


    // Initialize to the segment count, insert and delete size of a
    // swap in the path. assumes path_index points to the begining of 
    // a swap:
    //
    struct swap_info {
        swap_info(const path_t& path,
                  const unsigned path_index)
            : n_seg(path_index)
            , insert_length(0)
            , delete_length(0)
        {
            const unsigned aps(path.size());
            for(;(n_seg<aps) && is_segment_type_indel(path[n_seg].type);++n_seg) {
                const path_segment& ps(path[n_seg]);
                if     (ps.type==INSERT) { insert_length += ps.length; }
                else if(ps.type==DELETE) { delete_length += ps.length; }
                else                     { assert(0); }
            }
            n_seg -= path_index;
        }

        unsigned n_seg;
        unsigned insert_length;
        unsigned delete_length;
    };
}


#endif
