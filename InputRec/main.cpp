/*
 * Input Recorder
 *
 * Description:
 *     Records keyboard input into a replay file. This is useful for generating
 *     a "keyboard preview" for a video recording. Press F9 to start/stop the
 *     recording.
 *
 * Author:
 *     Clara Nguyen (@iDestyKK)
 */

#include "recorder.hpp"

using namespace std;

int main() {
	recorder<int> rec;
	int i;

	rec.record_start();

	//Demo a single loop
	for (i = 0; i < 1000000; i++) {};

	rec.record_capture(0);

	rec.record_stop();

	getchar();
}
