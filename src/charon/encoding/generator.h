/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * $Id$
 */

/**
 * @defgroup generator generator
 * @{ @ingroup encoding
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

typedef struct generator_t generator_t;

#include <library.h>
#include <encoding/payloads/encodings.h>
#include <encoding/payloads/payload.h>

/**
 * Generating is done in a data buffer.
 * This is the start size of this buffer in bytes.
 */
#define GENERATOR_DATA_BUFFER_SIZE 500

/**
 * Number of bytes to increase the buffer, if it is too small.
 */
#define GENERATOR_DATA_BUFFER_INCREASE_VALUE 500


/**
 * A generator_t class used to generate IKEv2 payloads.
 *
 * After creation, multiple payloads can be generated with the generate_payload
 * method. The generated bytes are appended. After all payloads are added, 
 * the write_to_chunk method writes out all generated data since
 * the creation of the generator. After that, the generator must be destroyed.
 * The generater uses a set of encoding rules, which it can get from
 * the supplied payload. With this rules, the generater can generate
 * the payload and all substructures automatically.
 */
struct generator_t {
	
	/**
	 * Generates a specific payload from given payload object.
	 *
	 * Remember: Header and substructures are also handled as payloads.
	 *
	 * @param payload 		interface payload_t implementing object
	 */
	void (*generate_payload) (generator_t *this,payload_t *payload);
	
	/**
	 * Writes all generated data of the generator to a chunk.
	 *
 	 * @param data 		chunk to write the data to
	 */
	void (*write_to_chunk) (generator_t *this,chunk_t *data);

	/**
	 * Destroys a generator_t object.
	 */
	void (*destroy) (generator_t *this);
};

/**
 * Constructor to create a generator.
 * 
 * @return generator_t object.
 */
generator_t *generator_create(void);

#endif /*GENERATOR_H_ @} */
