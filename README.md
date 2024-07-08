# Input Recorder

## Synopsis
A simple console application for logging key presses along with timestamp
information.

The file that it outputs is a binary file capable of being embedded in an MKV
file alongside gameplay. That's its intended purpose here. It provides key
pressing timestamp information down to the nanosecond, or whatever is the
fastest possible unit of time that the OS supports.

## How to use
Simply compile and run. Then press **F9** to record. Press it again to stop
recording. An output file will be made in the working directory called
`recording_TIMESTAMP.inp` where the timestamp is a nanosecond-precise timestamp
of when the recording started, multiplied by 1 billion.
