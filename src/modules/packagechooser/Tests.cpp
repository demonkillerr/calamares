/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Tests.h"

#include "PackageModel.h"

#include "utils/Logger.h"

#include <QtTest/QtTest>

QTEST_MAIN( PackageChooserTests )

PackageChooserTests::PackageChooserTests() {}

PackageChooserTests::~PackageChooserTests() {}

void
PackageChooserTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
PackageChooserTests::testBogus()
{
    QVERIFY( true );
}

void
PackageChooserTests::testAppData()
{
    // Path from the build-dir
    QString appdataName( "../io.calamares.calamares.appdata.xml" );
    QVERIFY( QFile::exists( appdataName ) );

    PackageItem p = PackageItem::fromAppData( appdataName );
#ifdef HAVE_XML
    QVERIFY( p.isValid() );
    QCOMPARE( p.id, "io.calamares.calamares.desktop" );
    QCOMPARE( p.name.get(), "Calamares" );
    // The <description> entry has precedence
    QCOMPARE( p.description.get(), "Calamares is an installer program for Linux distributions." );
    // .. but en_GB doesn't have an entry in description, so uses <summary>
    QCOMPARE( p.description.get( QLocale( "en_GB" ) ), "Calamares Linux Installer" );
    QCOMPARE( p.description.get( QLocale( "nl" ) ), "Calamares is een installatieprogramma voor Linux distributies." );
#else
    QVERIFY( !p.isValid() );
#endif
}
