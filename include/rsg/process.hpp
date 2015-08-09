/* Copyright (c) 2015. The SimGrid Team. All rights reserved.              */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero Licence (see in file LICENCE).        */

#ifndef SRC_RSG_PROCESS_HPP_
#define SRC_RSG_PROCESS_HPP_

#include <xbt.h>
#include <vector>

namespace simgrid {
namespace rsg {

class Process {
private:
	Process();
public:
	void sleep(double duration);

	/** Retrieves an instance of your representative in the remote SimGrid world */
	static Process &self();

private:
	static Process *p_self;

	/* To exchange data with the central server */
	int p_sock=-1;
	char *p_buffer;
	int p_buffer_size;
};
}} // namespace simgrid::rsg

#endif /* SRC_RSG_PROCESS_HPP_ */