#ifndef VALUE_H
#define VALUE_H

const void	*Add;
const void	*Sub;
const void	*Mult;
const void	*Div;
const void	*Minus;
const void	*Value;

void	*new(const void *type, ...);
void	process(const void *tree);
void	delete(void *tree);

#endif
