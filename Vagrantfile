require 'etc'

$init = <<SCRIPT
set -o errexit -o pipefail -o nounset
set -x

sudo apt update

install() {
  sudo apt-get install -y "$@"
}

# basic stuff
install wget curl software-properties-common

# helpers
install silversearcher-ag htop

# build tools
install yasm git cmake yasm nasm autoconf automake libtool g++ \
  pkg-config ccache valgrind clang

sudo ln -s /usr/bin/ccache /usr/local/bin/gcc
sudo ln -s /usr/bin/ccache /usr/local/bin/g++
sudo ln -s /usr/bin/ccache /usr/local/bin/cc
sudo ln -s /usr/bin/ccache /usr/local/bin/c++
ccache -M 0

sudo add-apt-repository -y ppa:ondrej/php
sudo apt-get update

install php7.1 php7.1-dev

SCRIPT

Vagrant.configure(2) do |config|
  config.vm.box_check_update = false

  config.vm.provision "shell", inline: $init

  config.vm.box = "boxcutter/ubuntu1604"

  if Vagrant.has_plugin?("vagrant-cachier")
    config.cache.scope = :box
    config.cache.enable :apt
  end

  config.vm.provider "virtualbox" do |vb|
    vb.memory = 1024
    vb.cpus = Etc.nprocessors
  end
end
