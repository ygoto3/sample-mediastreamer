# sample-mediastreamer

A sample mediastreamer using GStreamer.

## Dependencies

- GStreamer 1.0
- GTK+ 3
- CMake
- Conan
- pkg-config
- Scala
- Docker
- sql-migrate

## Build and run

### Build and run the applications

```sh
$ cd sample-mediastreamer/applications
$ mkdir build
$ cd build
$ conan install ..
$ cmake -G "Unix Makefiles" ..
$ make
$ open bin/sender.app
$ bin/receiver
$ bin/registrar
```

### Run database on Docker

```sh
$ cd sample-mediastreamer/database/scripts
$ ./docker-run.sh
$ ./init.sh
$ cd ..
$ sql-migrate up
```

### Run the server

```sh
$ cd sample-mediastreamer/server
$ sbt
sbt:mediastreamer-server> run
```

