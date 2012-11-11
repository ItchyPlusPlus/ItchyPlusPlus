# Maintainer: William Robson (logiblocs at gmail dot com)
pkgname=itchy-git
pkgver=VERSION
pkgrel=0
pkgdesc=""
arch=('i686' 'x86_64')
url="http://github.com/ItchyPlusPlus/ItchyPlusPlus"
license=('GPL')
groups=()
depends=('sdl' 'cairo')
makedepends=('git')
provides=()
conflicts=()
replaces=()
backup=()
options=()
source=()
noextract=()
md5sums=() #generate with 'makepkg -g'

_gitroot=git://github.com/ItchyPlusPlus/ItchyPlusPlus.git
_gitname=ItchyPlusPlus

build() {
  cd "$srcdir"
  msg "Connecting to GIT server...."

  if [[ -d "$_gitname" ]]; then
    cd "$_gitname" && git pull origin
    msg "The local files are updated."
  else
    git clone "$_gitroot" "$_gitname"
  fi

  msg "GIT checkout done or server timeout"
  msg "Starting build..."

  rm -rf "$srcdir/$_gitname-build"
  git clone "$srcdir/$_gitname" "$srcdir/$_gitname-build"
  cd "$srcdir/$_gitname-build/src"

  #build
  make
}

package() {
  cd "$srcdir/$_gitname-build/src"
  make INSTALL_PATH=usr "DESTDIR=$pkgdir" install
}

# vim:set ts=2 sw=2 et:
