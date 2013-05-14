/* 
    SAT_ExperimentData.h/cpp - wraps the experimental data in an object.

    Copyright (C) 2013 Jorge Ortiz for NanoSatisfi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
*/


/******************************************************************************
 * Includes
 ******************************************************************************/
#include "SAT_ExperimentData.h"


/******************************************************************************
 * Constructors
 ******************************************************************************/
SAT_ExperimentData::SAT_ExperimentData(uint32_t exp_id, uint32_t row_id, uint32_t col_id,
                                boolean fragment, uint32_t frag_idx, uint32_t frag_max,
                                payload_type_t ptype, uint8_t* value, size_t len)
{
    data_msg.exp_id = exp_id;
    data_msg.row_id = row_id;
    data_msg.col_id = col_id;
    data_msg.ptype = ptype;
    size_t wcnt = 0;

    data_msg.frag = fragment;
    data_msg.frag_idx = frag_idx;
    data_msg.frag_max = frag_max;;
    
    if(DATA_SIZE<len){
        wcnt = DATA_SIZE;
        /*data_msg.frag = true;
        data_msg.frag_idx = 0;
        data_msg.frag_max = (uint32_t)ceil((double)len/(double)DATA_SIZE);*/
    } else{
        wcnt = len;
    }
}

SAT_ExperimentData::SAT_ExperimentData(){}

/******************************************************************************
 * Experiment data API interface
 ******************************************************************************/
exp_data_t* SAT_ExperimentData::get_exp_data(){
    return &data_msg;
}

void SAT_ExperimentData::set_exp_id(uint32_t exp_id){
    data_msg.exp_id = exp_id;
}

uint32_t SAT_ExperimentData::get_exp_id(){
    return data_msg.exp_id;
}

void SAT_ExperimentData::set_row_id(uint32_t row_id){
    data_msg.row_id = row_id;
}

uint32_t SAT_ExperimentData::get_row_id(){
    return data_msg.row_id;
}

void SAT_ExperimentData::set_col_id(uint32_t col_id){
    data_msg.col_id = col_id;
}

uint32_t SAT_ExperimentData::get_col_id(){
    return data_msg.col_id;
}

