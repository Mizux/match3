# Scoring
[TOC]

# Basic {#scoring_basic}
To get Score you must align at least 3 items of the same color.  
Vertically or horizontally.
e.g.:

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| A   | "   | "   | "   | "   |
| A   | "   | "   | "   | "   |
| A   | "   | "   | "   | "   |
| "   | "   | "   | "   | "   |
| "   | B   | B   | B   | "   |

For a simple match of 3 items, all multiplier will be set to **x1**, thus a total
of **x3** for each group A and B.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| x1  | "   | "   | "   | "   |
| x1  | "   | "   | "   | "   |
| x1  | "   | "   | "   | "   |
| "   | "   | "   | "   | "   |
| "   | x1  | x1  | x1  | "   |

# Combo {#scoring_combo}
When an item can perform several 3 matches at a time, then it's multiplier
is incremented by the number of 3 matches it can contributes to.

## Match-4 combo {#scoring_combo_4}
Example for 4 in a column combo. Numbers indicate multiplier value.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| "   | x1  | "   | "   | "   |
| "   | X2  | "   | "   | "   |
| "   | x2  | "   | "   | "   |
| "   | x1  | "   | "   | "   |
| "   | "   | "   | "   | "   |

Example for 4 in a row combo. Numbers indicate multiplier value.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| "   | "   | "   | "   | "   |
| x1  | x2  | x2  | x1  | "   |
| "   | "   | "   | "   | "   |
| "   | "   | "   | "   | "   |
| "   | "   | "   | "   | "   |

Thus a total of **x6** !

## Match-5 combo {#scoring_combo_5}
Example for 5 in a column combo. Numbers indicate multiplier value.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| "   | x1  | "   | "   | "   |
| "   | x2  | "   | "   | "   |
| "   | x3  | "   | "   | "   |
| "   | x2  | "   | "   | "   |
| "   | x1  | "   | "   | "   |

Example for 5 in a row combo. Numbers indicate multiplier value.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| "   | "   | "   | "   | "   |
| x1  | x2  | x3  | x2  | x1  |
| "   | "   | "   | "   | "   |
| "   | "   | "   | "   | "   |
| "   | "   | "   | "   | "   |

Thus a total of **x9** !!

## Joint match {#scoring_combo_joint}
For "L", "T" and "Cross" shape only the joint item will get a **x2**
multiplier !

Example for "L" shape. Numbers indicate multiplier value.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| "   | "   | "   | "   | "   |
| x1  | "   | "   | "   | "   |
| x1  | "   | "   | "   | "   |
| x2  | x1  | x1  | "   | "   |
| "   | "   | "   | "   | "   |

Example for "T" shape. Numbers indicate multiplier value.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| "   | "   | "   | "   | "   |
| "   | x1  | x2  | x1  | "   |
| "   | "   | x1  | "   | "   |
| "   | "   | x1  | "   | "   |
| "   | "   | "   | "   | "   |

Example for "Cross" shape. Numbers indicate multiplier value.

| V   | V   | V   | V   | V   |
| :-: | :-: | :-: | :-: | :-: |
| "   | "   | "   | "   | "   |
| "   | "   | x1  | "   | "   |
| "   | x1  | x2  | x1  | "   |
| "   | "   | x1  | "   | "   |
| "   | "   | "   | "   | "   |
