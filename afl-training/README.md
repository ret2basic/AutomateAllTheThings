# afl-training

## Introduction

In this section, we are going to follow the "Fuzzing with AFL" workshop by [Michael Macnair](https://mobile.twitter.com/michael_macnair). The materials can be found at:

https://github.com/mykter/afl-training

## Setup

Set up the Docker container:

```shell
sudo docker run -d --privileged -p 2222:2222 -e PASSMETHOD=env -e PASS=<password> ghcr.io/mykter/fuzz-training
```

Connect to the Docker container:

```shell
ssh fuzzer@localhost -p 2222
```

## Levels

This training includes the following levels:

1. **vulnerable:** set up afl and get started.
2. **libxml2:** an ideal target, using ASAN and persistent mode.
3. **heartbleed:** infamous bug, using ASAN.
4. **sendmail/1301:** parallel fuzzing.
5. **ntpq:** fuzzing a network client; coverage analysis and increasing coverage.
6. **date:** fuzzing environment variable input.
7. **cyber-grand-challenge:** an easy vuln and an example of a hard to find vuln using afl.
8. **sendmail/1305:** persistent mode difficulties.
