/*
 * Recorder Class
 *
 * Description:
 *     Implements a generic recorder class for capturing events and outputting
 *     the contents to a file.
 *
 * Author:
 *     Clara Nguyen (@iDestyKK)
 */

#ifndef __RECORDER_HPP__
#define __RECORDER_HPP__

//C Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

//C++ Includes
#include <deque>
#include <chrono>

using namespace std;

// ----------------------------------------------------------------------------
// Recorder Class Prototype                                                {{{1
// ----------------------------------------------------------------------------

#define NOW() chrono::high_resolution_clock::now()

template <typename T>
class recorder {
    public:
		recorder();

		void record_start();
		void record_stop();

		void record_capture(const T &);

	private:
		struct ev_pair {
			ev_pair();
			ev_pair(const T &);
			ev_pair(const chrono::high_resolution_clock::time_point &,
				const T &);

			chrono::high_resolution_clock::time_point ts;
			T val;
		};

		void process();

		chrono::system_clock::time_point sys_start;
		chrono::high_resolution_clock::time_point start;
		chrono::high_resolution_clock::time_point end;

		deque<ev_pair> events;
};

#endif

#include "recorder.tpp"
