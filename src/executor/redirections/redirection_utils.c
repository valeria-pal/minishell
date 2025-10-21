
#include "executor.h"


static int apply_rd_in(t_redirection *rd,)
{
  int fd;
       fd = open (rd->filename,O_RDONLY );
      
       if(fd < 0)
       {
       	perror(rd->filename);  
       return (-1);
       }
       if ( dup2(fd, STDIN_FILENO) < 0 )
       {
        perror("dup2 stdin"); 
        close(fd);
       return (-1); 
       }
    close(fd);
    return 0;
}

static int apply_rd_out(t_redirection *rd)
{
  int fd;
fd = open (rd->filename,O_WRONLY| O_CREAT | O_TRUNC, 0644 );
    
       if(fd < 0)
       {
       	perror(rd->filename);  
       return (-1);
       }
		if (dup2(fd, STDOUT_FILENO) < 0)
     { perror("dup2 stdout");
       close(fd); 
       return (-1); 
      }
    close(fd);
    return 0;
}

static int apply_rd_append(t_redirection *rd)
{
int fd ;
fd = open (rd->filename,O_RDONLY| O_CREAT| O_APPEND, 0644);
  if(fd < 0)
       {
       	perror(rd->filename);  
       return (-1);
       }

if (dup2(fd, STDOUT_FILENO) < 0) { 
  perror("dup2 stdout"); 
  close(fd);
   return (-1); }

    close(fd);
    return 0;
}

int apply_heredoc(t_redirection *rd)
{
  int fd;
fd = open (rd->filename,O_RDONLY);
  if(fd < 0)
       {
       	perror(rd->filename);  
       return (-1);
       }
       if(dup2(fd, STDIN_FILENO)< 0)
       { perror("dup2 heredoc"); close(fd); return (-1); }
    close(fd);
    return 0;
}

int apply_redirect(t_redirection *rd)
{
      if (!rd || !rd->filename)
        return (-1);

    if (rd->type == REDIR_IN)
      return apply_rd_in(cmd->redirs);
    else if (rd->type == REDIR_OUT)
      return apply_rd_out(cmd->redirs);
    else if (rd_type == REDIR_APPEND)
    return apply_rd_append(cmd->redirs);
    else if (rd_type == HEREDOC)
    return apply_heredoc(cmd->redirs);
    perror("unknown redirection type\n");
    return (-1);
}


