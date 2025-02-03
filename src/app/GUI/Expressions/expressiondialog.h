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
#include <QDir>

#include "conncontext.h"
#include "dialogs/dialog.h"

class QrealAnimator;
class ExpressionEditor;
class PropertyBindingBase;

class JSLexer;
class JSEditor;

class QsciAPIs;

class ExpressionDialog : public Friction::Ui::Dialog
{
public:
    ExpressionDialog(QrealAnimator* const target,
                     QWidget * const parent = nullptr);

    void exportPreset(const QString& presetName);
    void importPreset(const QString& filePath = QString());

private:
    using PropertyBindingMap = std::map<QString, QSharedPointer<PropertyBindingBase>>;
    bool getBindings(PropertyBindingMap& bindings);
    void updateScriptBindings();
    void updateScriptDefinitions();
    void updateAllScript();
    void setCurrentTabId(const int id);
    bool apply(const bool action);
    void loadPresetCombo();
    void updatePresetCombo();
    bool checkPresetJSON(const QString& mPresetsDir, const QString& presetFile);

    QrealAnimator* const mTarget;

    QTabWidget *mTab;
    int mTabEditor;

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

    QDir mPresetsDir;
    QDir mPresetsDirUser;
    QComboBox* presetCombo;
};

#endif // EXPRESSIONDIALOG_H
