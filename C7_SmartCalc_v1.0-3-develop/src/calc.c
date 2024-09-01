#include "h_calc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayList(N *head) {
  N *tmp = head;

  while (tmp) {
    printf("value = %lf\t| ", tmp->value);
    printf("priority = %d\t\t| ", tmp->priority);
    printf("type = %d\t\t| ", tmp->type);
    printf("next = %p\t|\n", tmp->next);
    printf("------------------------\n");

    tmp = tmp->next;
  }

  printf("\n");
}

int check_error(char *str) {
  int ERROR = 0;
  int open_bracket_counter = 0, close_bracket_counter = 0;
  for (int i = 0; i < (int)strlen(str) && !ERROR; i++) {
    if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
         str[i] == '^' || str[i] == 'd') &&
        (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' ||
         str[i + 1] == '/' || str[i + 1] == '^' || str[i + 1] == 'm' ||
         !str[i + 1]))
      ERROR = 1;
    if ((str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == 'm') &&
        !str[i - 1])
      ERROR = 1;
    if ((str[i] == '.' || str[i] == ',') &&
        ((char)str[i + 1] < 48 || (char)str[i + 1] > 57 ||
         (char)str[i - 1] < 48 || (char)str[i - 1] > 57))
      ERROR = 1;
    if ((str[i] == '(' && (char)str[i - 1] >= 48 && (char)str[i - 1] <= 57) ||
        (str[i] == '(' && str[i + 1] == ')') ||
        (str[i] == '(' && (str[i + 1] == 'm' || str[i + 1] == '/' ||
                           str[i + 1] == '*' || str[i + 1] == '^')))
      ERROR = 1;
    if ((str[i] == ')' && (char)str[i + 1] >= 48 && (char)str[i + 1] <= 57) ||
        (str[i] == ')' && (char)str[i + 1] == '(') ||
        (str[i] == ')' &&
         (str[i - 1] == 'd' || str[i - 1] == '+' || str[i - 1] == '-' ||
          str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^')))
      ERROR = 1;
    if (str[i] == '(')
      open_bracket_counter++;
    if (str[i] == ')') {
      if (open_bracket_counter > close_bracket_counter) {
        close_bracket_counter++;
      } else {
        ERROR = 1;
      }
    }
    if (((char)str[i] >= 48 && (char)str[i] <= 57) &&
        (str[i + 1] == 's' || str[i + 1] == 'c' || str[i + 1] == 't' ||
         str[i + 1] == 'a' || str[i + 1] == 'l')) {
      ERROR = 1;
    }
    if (!(((char)str[i] >= 48 && (char)str[i] <= 57) || str[i] == ')' ||
          str[i] == 'x') &&
        (str[i + 1] == '\0')) {
      ERROR = 1;
    }
  }
  if (open_bracket_counter != close_bracket_counter && !ERROR) {
    ERROR = 1;
  }

  return ERROR;
}

void push(N **input, double value, int priority, int type) {
  N *tmp = (N *)malloc(sizeof(N));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = (*input);
  (*input) = tmp;
}

N *parser(char *str, double xValue) {
  N *input = NULL;

  char numeric[256] = {0};
  int numeric_counter = 0;

  for (int i = 0; i < (int)strlen(str); i++) {
    if (((char)str[i] >= 48 && (char)str[i] <= 57) || str[i] == '.') {
      numeric[numeric_counter] = str[i];
      numeric_counter++;
      if (!(((char)str[i + 1] >= 48 && (char)str[i + 1] <= 57) ||
            str[i + 1] == '.')) {
        double value_numeric = atof(numeric);
        push(&input, value_numeric, 0, number);
        memset(numeric, 0, 256);
        numeric_counter = 0;
      }
    }
    else if (str[i] == 'x') {
      push(&input, xValue, 0, x);
    }
    else if (str[i] == '(') {
      push(&input, 0, 5, open_bracket);
    }
    else if (str[i] == ')') {
      push(&input, 0, 5, close_bracket);
    }
    else if (str[i] == '+') {
      if (!str[i - 1] || str[i - 1] == '(') {
        continue;
      } else {
        push(&input, 0, 1, plus);
      }
    }
    else if (str[i] == '-') {
      if (!str[i - 1] || str[i - 1] == '(') {
        push(&input, 0, 0, number);
      }
      push(&input, 0, 1, minus);
    }
    else if (str[i] == '*') {
      push(&input, 0, 2, multiple);
    }
    else if (str[i] == '/') {
      push(&input, 0, 2, divide);
    }
    else if (str[i] == '^') {
      push(&input, 0, 3, degree);
    }
    else if (str[i] == 'm') {
      push(&input, 0, 1, mod_enum);
      i = i + 2;
    }
    else if (str[i] == 'c') {
      push(&input, 0, 4, cosinus);
      i = i + 2;
    }
    else if (str[i] == 's') {
      if (str[i + 1] == 'i') {
        push(&input, 0, 4, sinus);
        i = i + 2;
      }
      if (str[i + 1] == 'q') {
        push(&input, 0, 4, sqrt_enum);
        i = i + 3;
      }
    }
    else if (str[i] == 't') {
      push(&input, 0, 4, tangens);
      i = i + 2;
    }
    else if (str[i] == 'a') {
      if (str[i + 1] == 'c') {
        push(&input, 0, 4, acosinus);
        i = i + 3;
      }
      if (str[i + 1] == 's') {
        push(&input, 0, 4, asinus);
        i = i + 3;
      }
      if (str[i + 1] == 't') {
        push(&input, 0, 4, atangens);
        i = i + 3;
      }
    }
    else if (str[i] == 'l') {
      if (str[i + 1] == 'n') {
        push(&input, 0, 4, ln_enum);
        i = i + 1;
      }
      if (str[i + 1] == 'o') {
        push(&input, 0, 4, log_enum);
        i = i + 2;
      }
    }
  }
  return input;
}

N *reverse_input(N *input) {
  N *rev_input = NULL;
  while (input) {
    push(&rev_input, input->value, input->priority, input->type);
    input = input->next;
  }
  return rev_input;
}

N *pop(N **stack) {
  N *pop_stack;
  pop_stack = *stack;
  *stack = (*stack)->next;
  return pop_stack;
}

N *push_to_ready(N *rev_input) {
  N *ready = NULL;
  N *support = NULL;
  N *pop_support = NULL;

  while (rev_input) {
    if (rev_input->type == open_bracket) {
      push(&support, rev_input->value, rev_input->priority, rev_input->type);
      rev_input = rev_input->next;
    } else if (rev_input->type == close_bracket) {
      while (
          support->type !=
          open_bracket) {
        pop_support =
            pop(&support);
        push(&ready, pop_support->value, pop_support->priority,
             pop_support->type);
      }
      pop(&support);
      rev_input = rev_input->next;
    } else if (rev_input->priority ==
               0) {
      push(&ready, rev_input->value, rev_input->priority, rev_input->type);
      rev_input = rev_input->next;
    } else {
      if ((support == NULL) || (support->priority == 5) ||
          (support->priority <
           rev_input
               ->priority)) {
        push(&support, rev_input->value, rev_input->priority, rev_input->type);
        rev_input = rev_input->next;
      } else if (support->priority >=
                 rev_input->priority) {
        while ((support != NULL) &&
               (support->priority >= rev_input->priority) &&
               (support->priority !=
                5)) {
          pop_support = pop(
              &support);
          push(&ready, pop_support->value, pop_support->priority,
               pop_support->type);
        }
        push(&support, rev_input->value, rev_input->priority,
             rev_input->type);
        rev_input = rev_input->next;
      }
    }
  }
  while (support) {
    pop_support = pop(&support);
    push(&ready, pop_support->value, pop_support->priority, pop_support->type);
  }
  return ready;
}

double calc(N *rev_ready) {
  double res = rev_ready->value;

  N *calc_support = NULL;
  N *pop_rev_ready = NULL;
  int flag = 0;
  N *pop_calc_support = NULL;

  while (rev_ready != NULL) {
    if (rev_ready->priority == 0) {
      if ((rev_ready->next) &&
          (rev_ready->next->priority == 4)) {
        switch (rev_ready->next->type) {
        case cosinus:
          rev_ready->value =
              cos(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case sinus:
          rev_ready->value = sin(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case tangens:
          rev_ready->value = tan(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case acosinus:
          rev_ready->value = acos(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case asinus:
          rev_ready->value = asin(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case atangens:
          rev_ready->value = atan(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case sqrt_enum:
          rev_ready->value = sqrt(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case ln_enum:
          rev_ready->value = log(rev_ready->value);
          pop(&rev_ready->next);
          break;
        case log_enum:
          rev_ready->value = log10(rev_ready->value);
          pop(&rev_ready->next);
          break;
        }
      } else if ((rev_ready->next) && (rev_ready->next->priority == 0) &&
                 (rev_ready->next->next != NULL) &&
                 ((rev_ready->next->next->priority == 1) ||
                  (rev_ready->next->next->priority == 2) ||
                  (rev_ready->next->next->priority == 3))) {
        switch (rev_ready->next->next->type) {
        case plus:
          rev_ready->value += rev_ready->next->value;
          pop(&rev_ready->next);
          pop(&rev_ready->next);
          break;
        case minus:
          rev_ready->value -= rev_ready->next->value;
          pop(&rev_ready->next);
          pop(&rev_ready->next);
          break;
        case multiple:
          rev_ready->value *= rev_ready->next->value;
          pop(&rev_ready->next);
          pop(&rev_ready->next);
          break;
        case divide:
          rev_ready->value /= rev_ready->next->value;
          pop(&rev_ready->next);
          pop(&rev_ready->next);
          break;
        case degree:
          rev_ready->value = pow(rev_ready->value, rev_ready->next->value);
          pop(&rev_ready->next);
          pop(&rev_ready->next);
          break;
        case mod_enum:
          rev_ready->value = fmod(rev_ready->value, rev_ready->next->value);
          pop(&rev_ready->next);
          pop(&rev_ready->next);
          break;
        }
      } else {
        pop_rev_ready = pop(&rev_ready);
        push(&calc_support, pop_rev_ready->value, pop_rev_ready->priority,
             pop_rev_ready->type);
        flag = 1;
      }
    } else {
      while (calc_support) {
        pop_calc_support = pop(&calc_support);
        push(&rev_ready, pop_calc_support->value, pop_calc_support->priority,
             pop_calc_support->type);
      }
    }

    if ((rev_ready) && (rev_ready->next != NULL) &&
        (rev_ready->priority != 0) &&
        (flag == 0)) {
      rev_ready = rev_ready->next;
    }

    flag = 0;
    if ((rev_ready) && (rev_ready->value == reverse_input(rev_ready)->value) &&
        (rev_ready->priority == reverse_input(rev_ready)->priority) &&
        (rev_ready->priority == 0) && (rev_ready->next == NULL)) {
      break;
    } else if ((rev_ready) && (rev_ready->next == NULL) &&
               (rev_ready->priority == 0)) {
      break;
    }
  }
  return rev_ready ? rev_ready->value : res;
}
