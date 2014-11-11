pkgname=yawa-git
pkgver=0.0.1.r0.g1f4c8ac
pkgrel=1

pkgdesc='A tool which allows you to compose wallpapers for X.'
url='http://git.kyriasis.com/kyrias/yawa/about/'
arch=('i686' 'x86_64')
license=('GPL')

depends=('imlib2' 'libx11')
makedepends=('git')

source=('git+http://git.kyriasis.com/kyrias/yawa')

sha1sums=('SKIP')

pkgver() {
	cd yawa
	git describe --long | sed -r 's/([^-]*-g)/r\1/;s/-/./g'
}

build() {
	cd yawa
	cmake -g 'Unix Makefiles' . -DCMAKE_INSTALL_PREFIX=/usr
	make
}

package() {
  cd yawa
  make DESTDIR="$pkgdir" install
}
