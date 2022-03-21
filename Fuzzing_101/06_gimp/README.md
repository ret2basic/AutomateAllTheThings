# Fuzzing GIMP (Persisted Mode)





## Setup

Create a workspace:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/05_libxml2 && cd $PROJECT && mkdir fuzzing_gimp && cd fuzzing_gimp
```

Install dependencies:

```shell
sudo apt-get install build-essential libatk1.0-dev libfontconfig1-dev libcairo2-dev libgudev-1.0-0 libdbus-1-dev libdbus-glib-1-dev libexif-dev libxfixes-dev libgtk2.0-dev python2.7-dev libpango1.0-dev libglib2.0-dev zlib1g-dev intltool libbabl-dev
```

Install GEGL 0.2(Generic Graphics Library), which is another dependency:

```shell
wget https://download.gimp.org/pub/gegl/0.2/gegl-0.2.0.tar.bz2 && tar xvf gegl-0.2.0.tar.bz2 && cd gegl-0.2.0
```

