# ipc-sample

note: checkout with submodules.

## Inter-Process Communications (IPC)

[Aeron](https://github.com/real-logic/aeron/wiki) is an efficient message transport library for C++ and Java. It supports various channel configuration options including UDP ("udp://...." channels) and shared memory ("aeron:ipc" channel). Each channel can have multiple streams of different data, set up using "stream id".

It requires 3 parts to run

* **Driver**: broker that often runs in a separate process
* **Publisher**: sends binary data on a channel and stream id (in this case image data from C++)
* **Subscriber**: receives binary data (in this case a JavaFX UI)


## Testing

* Download this test version of Scope: https://hebifiles.z13.web.core.windows.net/internal/tpac/scope-1.7.5-999-windows-amd64_TPAC.zip
* run `bin/AeronDriver.exe` (driver)
* run `bin/TfmImageViewer.exe` (subscriber)
* build and run the cpp main. The image viewer should show a color changing image.

## Serialization

For converting the image data to a binary format I'm currently using protobuf v3.2.0. It is a relatively old version, but I didn't have time to figure out an appropriate cmake configuration for a new version (and it doesn't matter for this demo).

The protobuf files can be re-generated using

```bash
cd protocol
protoc-3.2.0-win32.exe --cpp_out=. rima.proto
```