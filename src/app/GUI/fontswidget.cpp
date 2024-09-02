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

#include "fontswidget.h"
#include "mainwindow.h"

#include <QLineEdit>
#include <QIntValidator>
#include <QLabel>

#include "widgets/editablecombobox.h"

FontsWidget::FontsWidget(QWidget *parent)
    : QWidget(parent)
    , mBlockEmit(0)
    , mBlockTextUpdate(false)
    , mMainLayout(nullptr)
    , mFontFamilyCombo(nullptr)
    , mFontStyleCombo(nullptr)
    , mFontSizeCombo(nullptr)
    , mAlignLeft(nullptr)
    , mAlignCenter(nullptr)
    , mAlignRight(nullptr)
    , mAlignTop(nullptr)
    , mAlignVCenter(nullptr)
    , mAlignBottom(nullptr)
    , mTextInput(nullptr)
    , mColorButton(nullptr)
{
    mFontStyleCombo = new QComboBox(this);
    mFontStyleCombo->setMinimumWidth(20);
    mFontStyleCombo->setFocusPolicy(Qt::NoFocus);
    mFontStyleCombo->setToolTip(tr("Font style"));

    mFontFamilyCombo = new QComboBox(this);
    mFontFamilyCombo->setMinimumWidth(20);
    mFontFamilyCombo->setFocusPolicy(Qt::NoFocus);
    mFontFamilyCombo->setToolTip(tr("Font family"));

    mFontSizeCombo = new EditableComboBox(this, true);
    mFontSizeCombo->setMinimumWidth(20);
    mFontSizeCombo->setCompleter(nullptr);
    mFontSizeCombo->setMinimumContentsLength(3);
    mFontSizeCombo->setToolTip(tr("Font size"));

    mColorButton = new ColorAnimatorButton(QColor(Qt::white), this);
    mColorButton->setFocusPolicy(Qt::NoFocus);

    MainWindow::sGetInstance()->installNumericFilter(mFontSizeCombo);
    mFontSizeCombo->setValidator(new QDoubleValidator(1, 999, 2, mFontSizeCombo));

    mFontFamilyCombo->addItems(filterFonts());

    connect(mFontFamilyCombo, &QComboBox::currentTextChanged,
            this, &FontsWidget::afterFamilyChange);

    connect(mFontStyleCombo, &QComboBox::currentTextChanged,
            this, &FontsWidget::afterStyleChange);

    connect(mFontSizeCombo, &QComboBox::currentTextChanged,
            this, &FontsWidget::emitSizeChanged);

    mMainLayout = new QVBoxLayout(this);
    //mMainLayout->setSpacing(eSizesUI::widget);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);
    setLayout(mMainLayout);

    mFontFamilyCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mFontStyleCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mFontSizeCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

   // QLabel *fontFamilyLabel = new QLabel(tr("Family"), this);
   // QLabel *fontStyleLabel = new QLabel(tr("Style"), this);
  //  QLabel *fontSizeLabel = new QLabel(tr("Size"), this);

    QWidget *fontFamilyWidget = new QWidget(this);
    fontFamilyWidget->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *fontFamilyLayout = new QHBoxLayout(fontFamilyWidget);
    fontFamilyLayout->setMargin(0);
   // fontFamilyLayout->addWidget(fontFamilyLabel);
    fontFamilyLayout->addWidget(mFontFamilyCombo);

    QWidget *fontStyleWidget = new QWidget(this);
    fontStyleWidget->setContentsMargins(0, 0, 0 ,0);
    QHBoxLayout *fontStyleLayout = new QHBoxLayout(fontStyleWidget);
    fontStyleLayout->setMargin(0);

  //  fontStyleLayout->addWidget(fontStyleLabel);
    fontStyleLayout->addWidget(mFontStyleCombo);
  //  fontStyleLayout->addWidget(fontSizeLabel);
    fontStyleLayout->addWidget(mFontSizeCombo);
    fontStyleLayout->addWidget(mColorButton);

    mMainLayout->addWidget(fontFamilyWidget);
    mMainLayout->addWidget(fontStyleWidget);

    mAlignLeft = new QPushButton(QIcon::fromTheme("alignLeft"),
                                 QString(), this);
    mAlignLeft->setFocusPolicy(Qt::NoFocus);
    mAlignLeft->setToolTip(tr("Align Text Left"));
    connect(mAlignLeft, &QPushButton::pressed,
            this, [this]() { emit textAlignmentChanged(Qt::AlignLeft); });

    mAlignCenter = new QPushButton(QIcon::fromTheme("alignCenter"),
                                   QString(), this);
    mAlignCenter->setFocusPolicy(Qt::NoFocus);
    mAlignCenter->setToolTip(tr("Align Text Center"));
    connect(mAlignCenter, &QPushButton::pressed,
            this, [this]() { emit textAlignmentChanged(Qt::AlignCenter); });

    mAlignRight = new QPushButton(QIcon::fromTheme("alignRight"),
                                  QString(), this);
    mAlignRight->setFocusPolicy(Qt::NoFocus);
    mAlignRight->setToolTip(tr("Align Text Right"));
    connect(mAlignRight, &QPushButton::pressed,
            this, [this]() { emit textAlignmentChanged(Qt::AlignRight); });

    mAlignTop = new QPushButton(QIcon::fromTheme("alignTop"),
                                QString(), this);
    mAlignTop->setFocusPolicy(Qt::NoFocus);
    mAlignTop->setToolTip(tr("Align Text Top"));
    connect(mAlignTop, &QPushButton::pressed,
            this, [this]() { emit textVAlignmentChanged(Qt::AlignTop); });

    mAlignVCenter = new QPushButton(QIcon::fromTheme("alignVCenter"),
                                    QString(), this);
    mAlignVCenter->setFocusPolicy(Qt::NoFocus);
    mAlignVCenter->setToolTip(tr("Align Text Center"));
    connect(mAlignVCenter, &QPushButton::pressed,
            this, [this]() { emit textVAlignmentChanged(Qt::AlignCenter); });

    mAlignBottom = new QPushButton(QIcon::fromTheme("alignBottom"),
                                   QString(), this);
    mAlignBottom->setFocusPolicy(Qt::NoFocus);
    mAlignBottom->setToolTip(tr("Align Text Bottom"));
    connect(mAlignBottom, &QPushButton::pressed,
            this, [this]() { emit textVAlignmentChanged(Qt::AlignBottom); });

    eSizesUI::widget.add(mAlignLeft, [this](const int size) {
        Q_UNUSED(size)
        mAlignLeft->setFixedHeight(eSizesUI::button);
        mAlignCenter->setFixedHeight(eSizesUI::button);
        mAlignRight->setFixedHeight(eSizesUI::button);
        mAlignTop->setFixedHeight(eSizesUI::button);
        mAlignVCenter->setFixedHeight(eSizesUI::button);
        mAlignBottom->setFixedHeight(eSizesUI::button);
    });

    mTextInput = new QPlainTextEdit(this);
    mTextInput->setPalette(ThemeSupport::getDarkerPalette());
    mTextInput->setAutoFillBackground(true);
    mTextInput->setFocusPolicy(Qt::ClickFocus);
    mTextInput->setPlaceholderText(tr("Enter text ..."));
    connect(mTextInput, &QPlainTextEdit::textChanged,
            this, [this]() {
        emit textChanged(mTextInput->toPlainText());
    });

    const auto buttonsLayout = new QHBoxLayout;
    //buttonsLayout->setSpacing(eSizesUI::widget/5);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);

    buttonsLayout->addWidget(mAlignLeft);
    buttonsLayout->addWidget(mAlignCenter);
    buttonsLayout->addWidget(mAlignRight);
    //eSizesUI::widget.addSpacing(buttonsLayout);
    buttonsLayout->addWidget(mAlignTop);
    buttonsLayout->addWidget(mAlignVCenter);
    buttonsLayout->addWidget(mAlignBottom);

    mMainLayout->addWidget(mTextInput);
    mMainLayout->addLayout(buttonsLayout);

    afterFamilyChange();
}

void FontsWidget::updateStyles()
{
    mBlockEmit++;
    const QString currentStyle = fontStyle();

    mFontStyleCombo->clear();
    QStringList styles = mFontDatabase.styles(fontFamily());
    mFontStyleCombo->addItems(styles);

    if (styles.contains(currentStyle)) {
        mFontStyleCombo->setCurrentText(currentStyle);
    }
    mBlockEmit--;
}

void FontsWidget::afterFamilyChange()
{
    updateStyles();
    emitFamilyAndStyleChanged();
}

void FontsWidget::afterStyleChange()
{
    updateSizes();
    emitFamilyAndStyleChanged();
}

const QStringList FontsWidget::filterFonts()
{
    QStringList families = mFontDatabase.families();
    // "if the font family is available from two or more foundries the foundry name is included in the family name"

    // Yeah, that's not going to work. I get a lot of "family name [Bits]" and "family name [unknown]" from the font database.
    // This breaks font selection as skia expects the proper font family name (of course).

    // So ...
    QStringList fonts;
    for (int i = 0; i < families.size(); ++i) {
        QString font = families.at(i);
        if (font.startsWith(".")) { continue; } // get a lot of .someKindOfFont on macOS, ignore!
        if (font.contains("[") && font.contains("]")) {
            fonts << font.remove(QRegExp("\\[(.*)\\]")).trimmed();
        } else { fonts << font; }
    }
    fonts.removeDuplicates();
    return fonts;
}

void FontsWidget::updateSizes()
{
    mBlockEmit++;
    const QString currentSize = mFontSizeCombo->currentText();

    mFontSizeCombo->clear();
    QList<int> sizes = mFontDatabase.smoothSizes(fontFamily(), fontStyle());
    if (sizes.isEmpty()) { sizes = mFontDatabase.standardSizes(); }
    for (const int size : sizes) {
        mFontSizeCombo->addItem(QString::number(size));
    }

    if (currentSize.isEmpty()) {
        mFontSizeCombo->setCurrentIndex(0);
    } else {
        const int id = mFontSizeCombo->findText(currentSize);
        if (id != -1) { mFontSizeCombo->setCurrentIndex(id); }
        else { mFontSizeCombo->setCurrentText(currentSize); }
    }
    mBlockEmit--;
}

float FontsWidget::fontSize() const
{
    return mFontSizeCombo->currentText().toFloat();
}

QString FontsWidget::fontStyle() const
{
    return mFontStyleCombo->currentText();
}

QString FontsWidget::fontFamily() const
{
    return mFontFamilyCombo->currentText();
}

void FontsWidget::setCurrentBox(BoundingBox * const box)
{
    SkScalar fontSize = 0.;
    QString fontFamily;
    SkFontStyle fontStyle;
    QString fontText;
    if (const auto tBox = enve_cast<TextBox*>(box)) {
        fontSize = tBox->getFontSize();
        fontFamily = tBox->getFontFamily();
        fontStyle = tBox->getFontStyle();
        fontText = tBox->getCurrentValue();
        setEnabled(true);
        setColorTarget(tBox->getFillSettings()->getColorAnimator());
        setBoxTarget(tBox);
    } else {
        clearText();
        setDisabled(true);
        setColorTarget(nullptr);
        setBoxTarget(nullptr);
    }
    setDisplayedSettings(fontSize,
                         fontFamily,
                         fontStyle,
                         fontText);
}

static QString styleStringHelper(const int weight,
                                 const SkFontStyle::Slant slant)
{
    QString result;
    if (weight > SkFontStyle::kNormal_Weight) {
        if (weight >= SkFontStyle::kBlack_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Black");
        } else if (weight >= SkFontStyle::kExtraBold_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Extra Bold");
        } else if (weight >= SkFontStyle::kBold_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Bold");
        } else if (weight >= SkFontStyle::kSemiBold_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Demi Bold");
        } else if (weight >= SkFontStyle::kMedium_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Medium", "The Medium font weight");
        }
    } else {
        if (weight <= SkFontStyle::kThin_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Thin");
        } else if (weight <= SkFontStyle::kExtraLight_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Extra Light");
        } else if (weight <= SkFontStyle::kLight_Weight) {
            result = QCoreApplication::translate("QFontDatabase", "Light");
        }
    }
    if (slant == SkFontStyle::kItalic_Slant) {
        result += QLatin1Char(' ') + QCoreApplication::translate("QFontDatabase", "Italic");
    } else if (slant == SkFontStyle::kOblique_Slant) {
        result += QLatin1Char(' ') + QCoreApplication::translate("QFontDatabase", "Oblique");
    }
    if (result.isEmpty()) {
        result = QCoreApplication::translate("QFontDatabase", "Regular");
    }
    return result.simplified();
}

void FontsWidget::setDisplayedSettings(const float size,
                                       const QString &family,
                                       const SkFontStyle &style,
                                       const QString &text)
{
    qDebug() << "setDisplayedSettings" << size << family << text;
    mTextInput->blockSignals(true);
    mTextInput->setPlainText(text);
    mTextInput->blockSignals(false);

    mBlockEmit++;
    mFontFamilyCombo->setCurrentText(family);
    const QString styleStr = styleStringHelper(style.weight(), style.slant());
    if (styleStr.isEmpty()) {
        mFontStyleCombo->setCurrentIndex(0);
    } else {
        mFontStyleCombo->setCurrentText(styleStr);
    }

    const auto sizeStr = QString::number(size);
    const int id = mFontSizeCombo->findText(sizeStr);
    if (id != -1) { mFontSizeCombo->setCurrentIndex(id); }
    else { mFontSizeCombo->setCurrentText(sizeStr); }
    mBlockEmit--;
}

void FontsWidget::setText(const QString &text)
{
    mTextInput->blockSignals(true);
    mTextInput->setPlainText(text);
    mTextInput->blockSignals(false);
}

const QString FontsWidget::getText()
{
    return mTextInput->toPlainText();
}

void FontsWidget::setTextFocus()
{
    mTextInput->setFocus();
}

void FontsWidget::clearText()
{
    mTextInput->blockSignals(true);
    mTextInput->clear();
    mTextInput->blockSignals(false);
}

void FontsWidget::setColorTarget(ColorAnimator * const target)
{
    mColorButton->setColorTarget(target);
}

void FontsWidget::setBoxTarget(TextBox * const target)
{
    mBoxTarget.assign(target);
    if (target) {
        mBoxTarget << connect(this, &FontsWidget::fontSizeChanged,
                              target, [target](const qreal &value) {
            target->setFontSize(value);
            Document::sInstance->actionFinished();
        });
        mBoxTarget << connect(this, &FontsWidget::textChanged,
                              target, [target, this](const QString &value) {
            mBlockTextUpdate = true;
            target->prp_startTransform();
            target->setCurrentValue(value);
            target->prp_finishTransform();
            Document::sInstance->actionFinished();
            mBlockTextUpdate = false;
        });
        mBoxTarget << connect(this, &FontsWidget::fontFamilyAndStyleChanged,
                              target, [target](const QString &family,
                                               const SkFontStyle &style) {
            target->setFontFamilyAndStyle(family, style);
            Document::sInstance->actionFinished();
        });
        mBoxTarget << connect(this, &FontsWidget::textAlignmentChanged,
                              target, [target](const Qt::Alignment &align) {
            target->setTextHAlignment(align);
            Document::sInstance->actionFinished();
        });
        mBoxTarget << connect(this, &FontsWidget::textVAlignmentChanged,
                              target, [target](const Qt::Alignment &align) {
            target->setTextVAlignment(align);
            Document::sInstance->actionFinished();
        });
        mBoxTarget << connect(target, &Property::prp_currentFrameChanged,
                              this, [this, target]() {
            if (mBlockTextUpdate) { return; }
            setDisplayedSettings(target->getFontSize(),
                                 target->getFontFamily(),
                                 target->getFontStyle(),
                                 target->getCurrentValue());
        });
    }
}

void FontsWidget::emitFamilyAndStyleChanged()
{
    if (mBlockEmit) { return; }
    const auto family = fontFamily();
    const auto style = fontStyle();
    const int qWeight = mFontDatabase.weight(family, style);
    const int weight = QFontWeightToSkFontWeight(qWeight);
    const int width = SkFontStyle::kNormal_Width;
//    const bool italic = mFontDatabase.italic(family, style);
//    const auto slant = italic ? SkFontStyle::kItalic_Slant :
//                                SkFontStyle::kUpright_Slant;
    const auto qFont = mFontDatabase.font(family, style, 10);
    const auto slant = toSkSlant(qFont.style());
    const SkFontStyle skStyle(weight, width, slant);
    emit fontFamilyAndStyleChanged(family, skStyle);
}

void FontsWidget::emitSizeChanged()
{
    if (mBlockEmit) { return; }
    emit fontSizeChanged(fontSize());
}
