# Maintainer: Your Name <youremail@domain.com>
pkgname=itchy-git
pkgver=20120929
pkgrel=1
pkgdesc=""
arch=('i686')
url=""
license=('GPL')
groups=()
depends=()
makedepends=('git')
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
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
  mkdir itchy "$pkgidr/usr/bin" -p
  cp itchy "$pkgdir/usr/bin/"
}

# vim:set ts=2 sw=2 et:
