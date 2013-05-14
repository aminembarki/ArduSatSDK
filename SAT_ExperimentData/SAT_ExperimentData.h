/** @brief  Library to store experiment data.

    This is the library to use for storing your experiment data.
	
   Copyright 2013 NanoSatisfi, Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
	
    @author Jorge Ortiz and NanoSatisfi, Inc.
    @date May 2013
*/
#ifndef EXPERIMENT_DATA_H 
#define EXPERIMENT_DATA_H

#include <inttypes.h>
#include <Arduino.h>
#include <nanosat_message.h>

#define DATA_SIZE 32

/******************************************************************************
 * payload types
 ******************************************************************************/
typedef enum{
    RAW=        0, 
    INTEGER=    1,
    DOUBLE=     INTEGER<<1,
    FLOAT=      INTEGER<<2,
    CHAR=       INTEGER<<3,
    SHORT=      INTEGER<<4,
    LONG=       INTEGER<<5,
    SIGNED=     INTEGER<<6,
    UNSIGNED=   INTEGER<<7,

    TEMP=       0x1000,
    SPEC=       TEMP<<1,
    GEIGER=     TEMP<<2
}payload_type_t;

/******************************************************************************
 * Experiment data message
 ******************************************************************************/
typedef struct {
    uint32_t exp_id;    //experiment id
    uint32_t row_id;    //row id
    uint32_t col_id;    //col id
    boolean frag;       //fragment flag
    uint32_t frag_idx;  //fragment counter
    uint32_t frag_max;  //total number of fragments
    uint32_t ptype;     //payload type
    uint32_t len;       //amount of data in the paylad
    uint8_t payload[DATA_SIZE]; //payload buffer
} exp_data_t;


/******************************************************************************
 * Experiment data API interface
 ******************************************************************************/
class SAT_ExperimentData
{
    private:
        exp_data_t data_msg;
    public:
		/**Experiment Data constructor
			@param row_id - Row ID
			@param col_id -Column ID
			@param fragment - Fragment
			@param frag_idx - Fragment IDX
			@param frag_max - Fragment Max
			@param ptype - Ptype
			@param value - Pointer to value
			@param len - Length
        */
        SAT_ExperimentData(uint32_t exp_id, uint32_t row_id, uint32_t col_id,
                boolean fragment, uint32_t frag_idx, uint32_t frag_max,
                payload_type_t ptype, uint8_t* value, size_t len);
		
		/**Default Constructor. */
        SAT_ExperimentData();

		//---------------------
        //getters and setters
        //---------------------
		
		exp_data_t* get_exp_data();
		
		/**Sets the experiment ID
			@param exp_id - The experiment ID to set.
        */
		void set_exp_id(uint32_t exp_id);
		
		/**Gets the experiment ID */
		uint32_t get_exp_id();
		
		/**Sets the row ID
			@param row_id - The row ID to set.
        */
        
		void set_row_id(uint32_t row_id);
		
		/**Gets the current row ID */
        uint32_t get_row_id();
		
		/**Sets the column ID
			@param col_id - The column ID to set.
        */
        void set_col_id(uint32_t col_id);
		
		/**Gets the column ID */
        uint32_t get_col_id();
};
#endif
