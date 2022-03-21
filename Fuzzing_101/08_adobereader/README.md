# Fuzzing Adobe Reader (QEMU Mode)




## AFL++ QEMU Mode




## Setup

Install dependencies:

```shell
sudo apt install libxml2:i386
```

Download and install Adobe Reader 9.5.1:

```shell
wget ftp://ftp.adobe.com/pub/adobe/reader/unix/9.x/9.5.1/enu/AdbeRdr9.5.1-1_i386linux_enu.deb && sudo dpkg -i AdbeRdr9.5.1-1_i386linux_enu.deb
```

Test Adobe Reader:

```shell
/opt/Adobe/Reader9/bin/acroread --help
```

Download and extract the corpus:

```shell

```

Only keep file smaller than 2KB to speed up the fuzzing process:

```shell

```

