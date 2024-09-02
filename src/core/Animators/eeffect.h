/*
#
# Friction - https://friction.graphics
#
# Copyright (c) Friction contributors
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

#ifndef EEFFECT_H
#define EEFFECT_H
#include "staticcomplexanimator.h"

class CORE_EXPORT eEffect : public StaticComplexAnimator {
    Q_OBJECT
public:
    eEffect(const QString &name);

    void prp_setupTreeViewMenu(PropertyMenu * const menu);

    virtual void writeIdentifier(eWriteStream& dst) const = 0;
    virtual void writeIdentifierXEV(QDomElement& ele) const = 0;

    virtual bool skipZeroInfluence(const qreal relFrame) const {
        Q_UNUSED(relFrame)
        return true;
    }

    void prp_writeProperty_impl(eWriteStream& dst) const;
    void prp_readProperty_impl(eReadStream& src);

    void switchVisible();
    void setVisible(const bool visible);
    bool isVisible() const;
signals:
    void effectVisibilityChanged(bool);
private:
    bool mVisible = true;
};

#endif // EEFFECT_H
