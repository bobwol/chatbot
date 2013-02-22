/*
 * Copyright (C) 2012 Andres Pagliano, Gabriel Miretti, Gonzalo Buteler,
 * Nestor Bustamante, Pablo Perez de Angelis
 *
 * This file is part of LVK Chatbot.
 *
 * LVK Chatbot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LVK Chatbot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LVK Chatbot.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LVK_NLP_WORD_H
#define LVK_NLP_WORD_H

#include <QString>
#include <QDebug>
#include <QRegExp>
#include <QStringList>
#include <QList>
#include <QDataStream>
#include <QMetaType>

#include "nlp-engine/syntax.h"

namespace Lvk
{

/// \addtogroup Lvk
/// @{

namespace Nlp
{

/// \ingroup Lvk
/// \addtogroup Nlp
/// @{

/**
 * \brief The Word class provides information about a word such as lemma, PoS tag,
 *        alternative spells, etc.
 *
 * The Word class is used by Lemmatizer's to return the information about a sentence
 */
class Word
{
public:
    Word(const QString origWord = "", const QString normWord = "", const QString lemma = "")
        : origWord(origWord), normWord(normWord), lemma(lemma) { }

    QString origWord; ///< The original word
    QString normWord; ///< The normalized form of the original word
    QString lemma;    ///< Word lemma
    QString posTag;   ///< Word PoS tag
    QStringList altSpells; ///< Alternative spellings for the original word

    bool operator==(const Word &other) const
    {
        return origWord == other.origWord &&
                normWord == other.normWord &&
                lemma == other.lemma &&
                posTag == other.posTag &&
                altSpells == other.altSpells;
    }

    bool operator!=(const Word &other) const
    {
        return !this->operator==(other);
    }

    bool isStar() const
    {
        return origWord == STAR_OP ;
    }

    bool isPlus() const
    {
        return origWord == PLUS_OP;
    }

    bool isWildcard() const
    {
        return isPlus() || isStar();
    }

    bool isVariable() const
    {
        return QRegExp(VAR_DECL_REGEX).exactMatch(origWord);
    }

    bool isSymbol() const
    {
        return !isWildcard() && origWord.size() == 1 && !origWord[0].isLetterOrNumber();
    }

    bool isWord() const
    {
        return !isWildcard() && !isSymbol() && !isVariable();
    }
};


/**
 * This method adds support to print debug information of Word classes
 */
inline QDebug& operator<<(QDebug& dbg, const Word &w)
{
    dbg.space() << w.origWord << w.normWord << w.lemma << w.posTag /*<< w.altSpells*/;

    return dbg.maybeSpace();
}


/**
 * The WordList class provides a list of Word's
 */
typedef QList<Word> WordList;

/// @}

} // namespace Nlp

/// @}

} // namespace Lvk

#endif // LVK_NLP_WORD_H

