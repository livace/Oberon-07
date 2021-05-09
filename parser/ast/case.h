#pragma once

#include "case_label_list.h"
#include "statement_sequence.h"
#include "ast.h"

class Case : public Ast {
public:
    Case(CaseLabelList *label_list, StatementSequence *statement_sequence)
        : label_list_(label_list)
        , statement_sequence_(statement_sequence) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    CaseLabelList *labelList() {
        return label_list_;
    }

    StatementSequence *statementSequence() {
        return statement_sequence_;
    }

private:
    CaseLabelList *label_list_;
    StatementSequence *statement_sequence_;
};
