/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:27:59 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 23:00:55 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>

# define X_BASE "0123456789abcdef"
# define XX_BASE "0123456789ABCDEF"
# define DEC_BASE "0123456789"

# define THPOOL_MAX 32
# define THPOOL_SEM_NAME_BASE "._sem"

enum	e_err_codes
{
	TPE_INIT_INPUTS,
	TPE_INIT_INV_WRKS,
	TPE_INIT_MUTEX,
	TPE_INIT_SEM,
	TPE_INIT_TASK_POOL,
	TPE_INIT_THRD,
	TPE_SBMT_INPTS,
	TPE_SBMT_MLC,
	TPE_QUEUE_INPTS,
	TPE_THREAD_INPTS,
	TPE_THREAD_NO_TASK,
	TPE_THREAD_NO_FUNC
};

typedef int (* t_task_func)(void *, void *);

typedef struct	s_task
{
	size_t			ticket_nb;
	pthread_t		processing_thread;
	t_task_func		task_f;
	void			*args;
	void			*ret_p;
	int				exit_code;
	struct s_task	*next;
}	t_task;

typedef struct	s_thread_pool
{
	char			is_running;
	int				nb_workers;
	int				nb_available;
	int				nb_finished;
	int				__thpool_id;
	char			sem_name[64];
	pthread_t		_threads[THPOOL_MAX];
	char			_quit_requested[THPOOL_MAX];
	char			_isbroken_threads[THPOOL_MAX];
	void			*_th_exit_codes[THPOOL_MAX];
	char			mutex_isinit[8];
	pthread_mutex_t	queue_mutex;
	pthread_mutex_t	task_pool_mutex;
	pthread_mutex_t	tp_manip_mutex;
	pthread_mutex_t	failed_mutex;
	pthread_mutex_t	print_mutex;
	sem_t			*task_sem;		// Counts up when a task is posted.
									// Down when a task is taken from queue.
	t_task			*task_queue;
	t_task			*last_task;
	t_task			*task_pool;		// Pool of empty pre-malloced t_task elems linked together at init
							// to accelerate submission of tasks.
	t_task			*failed_tasks;
	size_t			failed_tasks_counter;
	size_t			completed_tasks_counter;
	size_t			ticket_counter;
}	t_thpool;

/// THREAD POOL API //////
int		thpool_init(t_thpool *tp, int nb_workers);
int		thpool_submit(t_thpool *tp, int (*task)(void *, void *), void *args, void *ret);
int		thpool_destroy(t_thpool *tp, int print_status_at_exit);

/// THREAD POOL UTILS /////
void	*__task_handler(void *tp);
int		__sentinel(void *nil, void *null);

/// TASK QUEUE UTILS ///////
ssize_t	thpool_task_queue_len(t_task *tlst);
int		thpool_task_push_front(t_task **tlst, t_task **last, t_task *tsk);
int		thpool_task_push_back(t_task **tlst, t_task **last, t_task *tsk);
int		thpool_task_pop_front(t_task **tlst, t_task **last, t_task **ret);
//int		thpool_task_pop_back(t_task **tlst, t_task **ret);
int		thpool_tasks_clear(t_task **tlst, t_task **last);

/// LIBFT UTILS //////
void	ft_memclear(void *p, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t buff_size);
int		ft_putnbr_buff(char *dest, ssize_t nb);
int		ft_calloc_p(size_t size, void **ret_p);
int		ft_free_p(void **ptr);
int		ft_printf(const char *fmt, ...);
int		ft_eprintf(const char *fmt, ...);
int		ft_vprintf(const char *fmt, va_list *va);

/// PRINT FUNCS //////
void	thpool_printf(t_thpool *tp, const char *fmt, ...);
void	thpool_print_status(t_thpool *tp);
void	thpool_print_current_tasks(t_thpool *tp);
void	thpool_print_failed_tasks(t_thpool *tp);
void	thpool_print_pre_closure_status(t_thpool *tp);

/// ERROR HANDLING ///////
int		repport_thpool_init_failed(int code, int ws);
int		repport_thpool_submit_failed(pthread_mutex_t *lock, int code);
int		repport_thpool_task_op_failed(int code);
void	*repport_thpool_thread_failed(pthread_mutex_t *lock, int code, int id);

#endif
