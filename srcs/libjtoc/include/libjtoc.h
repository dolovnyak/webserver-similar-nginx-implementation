/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libjtoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:28:19 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/05 23:37:25 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBJTOC_H
# define LIBJTOC_H


# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define KNRM				"\x1B[0m"
# define KRED				"\x1B[31m"
# define KGRN				"\x1B[32m"
# define KYEL				"\x1B[33m"
# define KBLU				"\x1B[34m"
# define KMAG				"\x1B[35m"
# define HASH_P				31
# define HASH_M				1000000009

# define FUNCTION_SUCCESS	0
# define FUNCTION_FAILURE	-1

# define BUF_SIZE			(1 << 18)
# define FLOAT_BUF_SIZE		12

# define F_RIGHT			(1 << 0)
# define F_ONLY_SPACES		(1 << 1)



enum						e_type
{
	none,
	integer,
	fractional,
	string,
	object,
	array
};

typedef struct				s_jnode
{
	enum e_type				type;
	char					*name;
	int						hash;
	void					*data;
	struct s_jnode			*right;
	struct s_jnode			*down;
}							t_jnode;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isdigit(int c);
char				*ft_itoa(int n);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
int					ft_strhash(const char *str);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
t_jnode						*jtoc_node_create(enum e_type type, char *name,
void *data);

void						jtoc_node_add_child(t_jnode *parent,
t_jnode *child);

t_jnode						*jtoc_node_get_by_path(t_jnode *root,
const char *path);

void						jtoc_node_clear(t_jnode *parent);

int							jtoc_remove_spaces(char **str);

int							jtoc_find(const char *str, const char s, int i,
																		int d);
int							jtoc_find_comma(const char *str, int i);

int							jtoc_read_file(const char *path, char **res);

int							jtoc_validate_field(const char *str, int b,
																		int e);

int							jtoc_validate_value(const char *str, int c,
																		int e);

int							jtoc_validate_number(const char *str, int b,
																		int e);
int							jtoc_validate_string(const char *str, int b,
																		int e);
int							jtoc_validate_object(const char *str, int b,
																		int e);
int							jtoc_validate_array(const char *str, int b,
																		int e);

t_jnode						*jtoc_parse(const char *str);

enum e_type					jtoc_get_field_type(char *f);

int							jtoc_parse_field(t_jnode *p, const char *str,
																int b, int e);

int							jtoc_parse_value(t_jnode *p, const char *str,
																int b, int e);

int							jtoc_parse_integer(t_jnode *p, const char *str,
																int b, int e);
int							jtoc_parse_fractional(t_jnode *p, const char *str,
																int b, int e);
int							jtoc_parse_string(t_jnode *p, const char *str,
																int b, int e);
int							jtoc_parse_object(t_jnode *p, const char *str,
																int b, int e);
int							jtoc_parse_array(t_jnode *p, const char *str,
																int b, int e);

t_jnode						*jtoc_read(const char *str);

int							jtoc_get_int(t_jnode *n);
float						jtoc_get_float(t_jnode *n);
char						*jtoc_get_string(t_jnode *n);

size_t						jtoc_get_child_count(t_jnode *n);

void						*jtoc_get_raw_data(t_jnode *n);

//jtoc_get_raw_data_help.c removed from cmake
int							jtoc_get_raw_data_help(t_jnode *cur, char *res, void **tmp, size_t *i);

int							jtoc_write_children(t_jnode *n, int fd,
																	char arr);

char						*jtoc_ftoa(float n, int flen);
int							jtoc_write(t_jnode *n, const char *str);
int							ft_isstn(char c);
#endif
