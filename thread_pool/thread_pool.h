/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:27:59 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/03 00:16:36 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include "libft.h"

# define THPOOL_MAX 32
# define THPOOL_SEM_NAME_BASE "._sem"

enum	e_err_codes
{
	TPE_INIT_INPUTS,
	TPE_INIT_INV_WRKS,
	TPE_INIT_MUTEX,
	TPE_INIT_SEM,
	TPE_SUBMIT_INPUTS,
	TPE_SUBMIT_MALLOC,
	TPE_QUEUE_INPUTS,
	TPE_THREAD_INPUTS,
	TPE_THREAD_NO_TASK
};

typedef struct	s_task
{
	size_t			ticket_nb;
	int				(*task_f)(void *args, void *ret);
	void			*args;
	void			*ret_p;
	int				is_done;
	int				has_failed;
	struct s_task	*next;
}	t_task;

typedef struct	s_thread_pool
{
	char			is_running;
	int				nb_workers;
	int				nb_available;
	int				__thpool_id;
	char			sem_name[32];
	pthread_t		_threads[THPOOL_MAX];
	char			_quit_requested[THPOOL_MAX];
	char			_isbroken_threads[THPOOL_MAX];
	void			*_th_return_vals[THPOOL_MAX];
	pthread_mutex_t	queue_mutex;
	pthread_mutex_t	failed_mutex;
	pthread_mutex_t	print_mutex;
	sem_t			*task_sem;		// Counts up when a task is posted.
									// Down when a task is taken from queue.
	t_task			*task_queue;
	t_task			*failed_tasks;
	size_t			failed_tasks_counter;
	size_t			ticket_counter;
}	t_thpool;

/// THREAD POOL FUNCS //////
int		thpool_init(t_thpool *tp, int nb_workers);
int		thpool_submit(t_thpool *tp, int (*task)(void *, void *), void *args, void *ret);
int		thpool_destroy(t_thpool *tp, int print_status_at_exit);

/// TASK QUEUE UTILS ///////
ssize_t	thpool_task_queue_len(t_task **tlst);
int		thpool_task_push_front(t_task **tlst, t_task *tsk);
int		thpool_task_push_back(t_task **tlst, t_task *tsk);
int		thpool_task_pop_front(t_task **tlst, t_task **ret);
int		thpool_task_pop_back(t_task **tlst, t_task **ret);
int		thpool_task_clear(t_task **tlst);

/// PRINT FUNCS //////
void	thpool_print_status(t_thpool *tp);

/// ERROR HANDLING ///////
int		repport_thpool_init_failed(int code, pthread_mutex_t *del_lock, int ws);
int		repport_thpool_submit_failed(pthread_mutex_t *lock, int code);
int		repport_thpool_task_op_failed(int code);
void	*repport_thpool_thread_failed(pthread_mutex_t *lock, int code, int id);

#endif
