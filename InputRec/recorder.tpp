#ifndef __RECORDER_TPP__
#define __RECORDER_TPP__

#include "recorder.hpp"

using namespace std;

// ----------------------------------------------------------------------------
// Recorder Class Function Definitions                                     {{{1
// ----------------------------------------------------------------------------

/*
 * useless constructor lol
 */

template <typename T>
recorder<T>::recorder() {

}

/*
 * record_start
 *
 * Starts a recording. This is simply logging start time (both via system and
 * high-resolution timer) and clearing the events queue.
 */

template <typename T>
void recorder<T>::record_start() {
	sys_start = chrono::system_clock::now();
	start = NOW();
	events.clear();
}

/*
 * record_stop
 *
 * Stops a recording. Will write the key presses to a "recording.inp" via
 * "process()".
 */

template <typename T>
void recorder<T>::record_stop() {
	end = chrono::high_resolution_clock::now();
}

/*
 * record_capture
 *
 * Captures an event and the exact moment it occurred.
 */

template <typename T>
void recorder<T>::record_capture(const T &v) {
	events.push_back(ev_pair(v));
}

/*
 * record_save
 *
 * Processes the times and events. Archives them into a file.
 */

template <typename T>
void recorder<T>::record_save(const string &fname) {
	FILE    *fp;
	char     head[5] = "IREC";
	uint32_t ver = 0;
	int64_t  s_time, d_time, ts;
	uint64_t e_cnt;

	typename deque<ev_pair>::iterator it;

	//Figure out when the recording started & ended w/ nanosecond precision
	s_time = chrono::duration_cast<chrono::nanoseconds>(
		sys_start.time_since_epoch()
	).count();

	d_time = chrono::duration_cast<chrono::nanoseconds>(
		end - start
	).count();

	//Open the file for writing
	fp = fopen(fname.c_str(), "wb");

	//Write header information (24)
	fwrite( head  , sizeof(char    ), 4, fp);  /* Magic Number (4) */
	fwrite(&ver   , sizeof(uint32_t), 1, fp);  /* Version      (4) */
	fwrite(&s_time, sizeof(int64_t ), 1, fp);  /* Start Time   (8) */
	fwrite(&d_time, sizeof(int64_t ), 1, fp);  /* Duration     (8) */

	//Number of events (8)
	e_cnt = events.size();
	fwrite(&e_cnt, sizeof(uint64_t), 1, fp);

	//Each event
	for (it = events.begin(); it != events.end(); it++) {
		ev_pair &e = *it;

		ts = chrono::duration_cast<chrono::nanoseconds>(e.ts - start).count();

		//Timestamp (8) and type written (varies)
		fwrite(&ts   , sizeof(int64_t), 1, fp);
		fwrite(&e.val, sizeof(T      ), 1, fp);
	}

	//We're done here.
	fclose(fp);
}

// ----------------------------------------------------------------------------
// recorder::ev_pair Struct Function Definitions                           {{{1
// ----------------------------------------------------------------------------

/*
 * constructors
 */

template <typename T>
recorder<T>::ev_pair::ev_pair() {
	ts  = NOW();
	val = T();
}

template <typename T>
recorder<T>::ev_pair::ev_pair(const T &v) {
	ts  = NOW();
	val = v;
}

template <typename T>
recorder<T>::ev_pair::ev_pair(
	const chrono::high_resolution_clock::time_point &t,
	const T &v
) {
	ts = t;
	val = v;
}

#endif
