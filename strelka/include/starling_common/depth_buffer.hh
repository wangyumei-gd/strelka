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

#ifndef __DEPTH_BUFFER_HH
#define __DEPTH_BUFFER_HH

#include "blt_util/blt_types.hh"

#include <map>


struct depth_buffer {

    unsigned
    val(const pos_t pos) const {
        const citer i(_data.find(pos));
        if(i == _data.end()) return 0;
        else                 return i->second;
    }

    void
    inc(const pos_t pos) {
        const iter i(_data.find(pos));
        if(i == _data.end()) _data[pos] = 1;
        else                 i->second += 1;
    }

    void
    clear_pos(const pos_t pos) {
        _data.erase(pos);
    }

private:
    typedef std::map<pos_t,unsigned> count_t;
    typedef count_t::iterator iter;
    typedef count_t::const_iterator citer;

    count_t _data;
};


#endif
