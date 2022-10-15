
int lock_reg(int fd, int cmd, short lock_type, short lock_whence, off_t lock_start, off_t lock_len)
{
    struct flock lock;
    lock.l_type = lock_type;
    lock.l_whence = lock_whence;
    lock.l_start = lock_start;
    lock.l_len = lock_len;
    lock.l_pid = getpid(); //锁进程

    if (fcntl(fd, cmd, &lock) < 0)
    {
        if (errno == EACCES || errno == EAGAIN)
        {
            printf("file lock by other processes.\n");
            return -1;
        }
        printf("lock file fail.\n");
        return -1;
    }

    if (lock_type == F_WRLCK)
    {
        printf("lock by %d.\n", getpid());
    }
    else if (lock_type == F_UNLCK)
    {
        printf("unlock by %d.\n", getpid());
    }

    return 0;
}

int reg_lock(int fd)
{
    //cmd = F_SETLK    :上锁(非阻塞)  , 失败直接返回 -1
    //l_type = F_WRLCK  :写锁
    //l_whence = 0      :起始位置
    //l_start = 0       :偏移量
    //l_len = 0         :长度
    return lock_reg(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0);
}

int reg_unlock(int fd)
{
    //cmd = F_SETLK    :上锁(非阻塞), 失败直接返回 -1
    //l_type = F_UNLCK  :无锁
    //l_whence = 0      :起始位置
    //l_start = 0       :偏移量
    //l_len = 0         :长度
    return lock_reg(fd, F_SETLK, F_UNLCK, 0, SEEK_SET, 0);
}

int reg_lockw(int fd)
{
    //cmd = F_SETLKW    :上锁(阻塞)
    //l_type = F_WRLCK  :写锁
    //l_whence = 0      :起始位置
    //l_start = 0       :偏移量
    //l_len = 0         :长度
    return lock_reg(fd, F_SETLKW, F_WRLCK, 0, SEEK_SET, 0);
}
int reg_unlockw(int fd)
{
    //cmd = F_SETLKW    :上锁(阻塞)
    //l_type = F_UNLCK  :无锁
    //l_whence = 0      :起始位置
    //l_start = 0       :偏移量
    //l_len = 0         :长度
    return lock_reg(fd, F_SETLKW, F_UNLCK, 0, SEEK_SET, 0);
}

#define FileName "商品.txt"
/********* 生产者 *******/
//锁的作用：保护文件的安全性
int main()
{
    int fd = open(FileName, O_RDWR | O_CREAT | O_APPEND, 0777); //打开文件

    int ok = reg_lockw(fd); //阻塞式上锁
    if (ok == -1)
    {
        printf("上锁失败");
        return -1;
    }
    char buf[128] = "";
    int len = sizeof(buf);

    memset(buf,0,len);
    read(fd,buf,len);

    printf("消费了:%s\n",buf);

    remove(FileName);
    //生产完了就解锁
    ok = reg_unlockw(fd); //阻塞式解锁
    if (ok == -1)
    {
        printf("解锁失败");
        return -1;
    }
}