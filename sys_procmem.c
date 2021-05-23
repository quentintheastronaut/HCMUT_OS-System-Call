#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

struct proc_segs {

    unsigned long mssv;
    unsigned long start_code;
    unsigned long end_code;
    unsigned long start_data;
    unsigned long end_data;
    unsigned long start_heap;
    unsigned long end_heap;
    unsigned long start_stack;
};

asmlinkage long sys_procmem(int pid, struct proc_segs * info){

    struct task_struct * proc;
    struct proc_segs buff;

    for_each_process(proc){
        if(proc->pid == pid){
            if(proc->mm != NULL){

                buff.mssv = 1813694;
                buff.start_code = proc->mm->start_code;
                buff.end_code = proc->mm->end_code;
                buff.start_data = proc->mm->start_data;
                buff.end_data = proc->mm->end_data;
                buff.start_heap = proc->mm->start_brk;
                buff.end_heap = proc->mm->brk;
                buff.start_stack = proc->mm->start_stack;

                int flag = copy_to_user(info,&buff,sizeof(buff));

                if(flag == 0){
                    return 0;
                }
                else {
                    return -1;
                }
            }
        }
    }

    return -1;
}
