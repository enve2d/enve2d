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

#ifndef EXPRESSIONDIALOG_H
#define EXPRESSIONDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include "conncontext.h"

class QrealAnimator;
class ExpressionEditor;
class PropertyBindingBase;

class JSLexer;
class JSEditor;

class QsciAPIs;

class ExpressionDialog : public QDialog
{
public:
    ExpressionDialog(QrealAnimator* const target,
                     QWidget * const parent = nullptr);

private:
    using PropertyBindingMap = std::map<QString, QSharedPointer<PropertyBindingBase>>;
    bool getBindings(PropertyBindingMap& bindings);
    void updateScriptBindings();
    void updateScriptDefinitions();
    void updateAllScript();
    void setCurrentTabId(const int id);
    bool populateEasingPresets();
    bool apply(const bool action);

    QrealAnimator* const mTarget;

    QTabWidget *mTab;
    int mTabEasingPreset;
    int mTabEditor;

    QComboBox *mEasingPresetsBox;
    QDoubleSpinBox *mEasingPresetStartValueSpin;
    QDoubleSpinBox *mEasingPresetEndValueSpin;
    QSpinBox *mEasingPresetStartFrameSpin;
    QSpinBox *mEasingPresetEndFrameSpin;

    QIcon mRedDotIcon;

    QPushButton* mBindingsButton;
    QPushButton* mDefinitionsButon;

    QLabel* mBindingsLabel;
    ExpressionEditor* mBindings;
    QLabel* mBindingsError;

    QLabel* mDefsLabel;
    JSLexer* mDefsLexer;
    JSEditor* mDefinitions;
    QsciAPIs* mDefinitionsApi;
    QLabel* mDefinitionsError;

    JSLexer* mScriptLexer;
    bool mBindingsChanged = true;
    bool mDefinitionsChanged = true;
    QLabel* mScriptLabel;
    JSEditor* mScript;
    QsciAPIs* mScriptApi;
    QLabel* mScriptError;

    ConnContext mAutoApplyConn;
};

#endif // EXPRESSIONDIALOG_H
