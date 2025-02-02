/*
#
# Friction - https://friction.graphics
#
# Copyright (c) Ole-André Rodlie and contributors
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# See 'README.md' for more information.
#
*/

// Fork of enve - Copyright (C) 2016-2020 Maurycy Liebner

#ifndef XMLEXPORTHELPERS_H
#define XMLEXPORTHELPERS_H

#include "../exceptions.h"

#include "../skia/skiaincludes.h"

#include <QDomElement>
#include <QString>

class SimpleBrushWrapper;
class Property;

namespace Friction
{
    namespace Core
    {
        class XmlImporter;
        class XmlExporter;

        class CORE_EXPORT XmlExportHelpers
        {
        public:
            static SkBlendMode stringToBlendMode(const QString& compOpStr);
            static QString blendModeToString(const SkBlendMode blendMode);
            static qreal stringToDouble(const QStringRef& string);
            static qreal stringToDouble(const QString& string);
            static int stringToInt(const QStringRef& string);
            static int stringToInt(const QString& string);

            template <typename T, typename S>
            static T stringToEnum(const S& string) {
                const int intVal = stringToInt(string);
                return static_cast<T>(intVal);
            }

            template <typename T, typename S>
            static T stringToEnum(const S& string, const T min, const T max) {
                const auto result = stringToEnum<T>(string);
                if(result < min || result > max)
                    RuntimeThrow("Value outside of enum value range");
                return result;
            }

            template <typename T, typename S>
            static T stringToEnum(const S& string, const T max) {
                return stringToEnum(string, 0, max);
            }

            static QMatrix stringToMatrix(const QString& str);
            static QString matrixToString(const QMatrix& m);
        };

        namespace XevExportHelpers
        {
            CORE_EXPORT
            QDomElement brushToElement(SimpleBrushWrapper* const brush,
                                       QDomDocument& doc);
            CORE_EXPORT
            SimpleBrushWrapper* brushFromElement(const QDomElement& ele);

            CORE_EXPORT
            void setAbsAndRelFileSrc(const QString& absSrc,
                                     QDomElement& ele,
                                     const XmlExporter& exp);
            CORE_EXPORT
            QString getAbsAndRelFileSrc(const QDomElement& ele,
                                        const XmlImporter& imp);
            CORE_EXPORT
            bool writeProperty(QDomElement& ele, const XmlExporter& exp,
                               const QString& name, Property* const prop);
            CORE_EXPORT
            bool readProperty(const QDomElement& ele, const XmlImporter& imp,
                              const QString& name, Property* const prop);
        };
    }
}

#endif // XMLEXPORTHELPERS_H
