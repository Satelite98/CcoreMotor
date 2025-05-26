/**
 * @file shell_companion.c
 * @author Letter (nevermindzzt@gmail.com)
 * @brief shell companion object support
 * @version 3.0.3
 * @date 2020-07-22
 * 
 * @copyright (c) 2020 Letter
 * 
 */
 #include "shell.h"
 
#if SHELL_USING_COMPANION == 1
/**
 * @brief shell��Ӱ�������
 * 
 * @param shell shell����
 * @param id ��������ID
 * @param object ��������
 * @return signed char 0 ��ӳɹ� -1 ���ʧ��
 */
signed char shellCompanionAdd(Shell *shell, int id, void *object)
{
    ShellCompanionObj *companions = shell->info.companions;
    ShellCompanionObj *node = SHELL_MALLOC(sizeof(ShellCompanionObj));
    SHELL_ASSERT(node, return -1);
    node->id = id;
    node->obj = object;
    node->next = companions;
    shell->info.companions = node;
    return 0;
}

/**
 * @brief shellɾ����������
 * 
 * @param shell shell����
 * @param id ��������ID
 * @return signed char 0 ɾ���ɹ� -1 ��ƥ�����
 */
signed char shellCompanionDel(Shell *shell, int id)
{
    ShellCompanionObj *companions = shell->info.companions;
    ShellCompanionObj *front = companions;
    while (companions)
    {
        if (companions->id == id)
        {
            if (companions == shell->info.companions && !(companions->next)) 
            {
                shell->info.companions = (void *)0;
            }
            else
            {
                front->next = companions->next;
            }
            SHELL_FREE(companions);
            return 0;
        }
        front = companions;
        companions = companions->next;
    }
    return -1;
}

/**
 * @brief shell��ȡ��������
 * 
 * @param shell shell����
 * @param id ��������ID
 * @return void* ����������ƥ�����ʱ����NULL
 */
void *shellCompanionGet(Shell *shell, int id)
{
    SHELL_ASSERT(shell, return (void *)0);
    ShellCompanionObj *companions = shell->info.companions;
    while (companions)
    {
        if (companions->id == id)
        {
            return companions->obj;
        }
        companions = companions->next;
    }
    return (void *)0;
}
#endif /** SHELL_USING_COMPANION == 1 */
