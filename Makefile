##
## EPITECH PROJECT, 2022
## SFMLgame
## File description:
## Makefile
##

# -----------------------------------------------------------
# Target

NAME = pbrain_agin

#------------------------------------------------------------
# COLOUR

CYAN = '\033[1;36m'
GREEN = '\033[1;32m'
RED = '\033[1;31m'
BLUE = '\033[1;34m'

RESET = '\033[0m'

#------------------------------------------------------------
# IN-MAKEFILE

BINARY_PATH 	:=	$(shell stack path --local-install-root)
CURR_RULE = all
CC := g++
RM = rm -rf
CP = cp

#------------------------------------------------------------
# Make the name
$(NAME): CURR_RULE = $(NAME)
$(NAME): init
	cmake -S . -B build
	cmake --build build -j 10
	cp ./build/bin/pbrain_agin ./$(NAME)

#------------------------------------------------------------
# Clean

.PHONY : init
clean : CURR_RULE = clean
clean: init
	$(RM) ./build
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(CURR_RULE)'$(RESET)

#------------------------------------------------------------
# fclean

.PHONY: fclean
fclean: CURR_RULE = fclean
fclean: init clean
	$(RM) $(NAME)
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(CURR_RULE)'$(RESET)

#------------------------------------------------------------
# Re

.PHONY: re
re:		CURR_RULE = re
re:		init fclean
	@$(MAKE) $(NAME)
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(CURR_RULE)'$(RESET)

#------------------------------------------------------------
# Print

.PHONY: init
init:
	@echo -e $(CYAN)'-> [starting]: $(NAME): make $(CURR_RULE)'$(RESET)