/**
 * @file shell_ext.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief shell extensions
 * @version 3.0.0
 * @date 2019-12-31
 * 
 * @copyright (c) 2019 Letter
 * 
 */


#ifdef __GNUC__
#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-compare"

#endif



#ifdef __HIGHTEC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

#ifdef __ghs__

#pragma ghs nowarning 1518

#endif


#include "shell_cfg.h"
#include "shell.h"
#include "shell_ext.h"
#include "string.h"

extern ShellCommand* shellSeekCommand(Shell *shell,
                                      const char *cmd,
                                      ShellCommand *base,
                                      unsigned short compareLength);
extern int shellGetVarValue(Shell *shell, ShellCommand *command);

#if SHELL_USING_FUNC_SIGNATURE == 1
/**
 * @brief ��ȡ��һ����������
 * 
 * @param signature ����ǩ��
 * @param index ����������ǩ���е���ʼ����
 * @param type ��ȡ���Ĳ�������
 * 
 * @return int ��һ��������ǩ���е�����
 */
static int shellGetNextParamType(const char *signature, int index, char *type)
{
    const char *p = signature + index;
    if (*p == 'L')
    {
        while (*p != ';' && *p != 0)
        {
            *type++ = *p++;
            index++;
        }
        *type++ = *p++;
        index++;
    }
    else if (*p != 0)
    {
        *type++ = *p;
        index++;
    }
    *type = '\0';
    return index;
}


static int shellGetParamNumExcept(const char *signature)
{
    int num = 0;
    const char *p = signature;
    
    while (*p)
    {
        if (*p == 'L')
        {
            while (*p != ';' && *p != 0)
            {
                p++;
            }
            p++;
        }
        else
        {
            p++;
        }
        num++;
    }
    return num;
}
#endif

/**
 * @brief �ж����ֽ���
 * 
 * @param string �����ַ���
 * @return ShellNumType ����
 */
static ShellNumType shellExtNumType(char *string)
{
    char *p = string;
    ShellNumType type = NUM_TYPE_DEC;

    if ((*p == '0') && ((*(p + 1) == 'x') || (*(p + 1) == 'X')))
    {
        type = NUM_TYPE_HEX;
    }
    else if ((*p == '0') && ((*(p + 1) == 'b') || (*(p + 1) == 'B')))
    {
        type = NUM_TYPE_BIN;
    }
    else if (*p == '0')
    {
        type = NUM_TYPE_OCT;
    }
    
    while (*p++)
    {
        if (*p == '.' && *(p + 1) != 0)
        {
            type = NUM_TYPE_FLOAT;
            break;
        }
    }

    return type;
}


/**
 * @brief �ַ�ת����
 * 
 * @param code �ַ�
 * @return char ����
 */
static char shellExtToNum(char code)
{
    if ((code >= '0') && (code <= '9'))
    {
        return code -'0';
    }
    else if ((code >= 'a') && (code <= 'f'))
    {
        return code - 'a' + 10;
    }
    else if ((code >= 'A') && (code <= 'F'))
    {
        return code - 'A' + 10;
    }
    else
    {
        return 0;
    }
}


/**
 * @brief �����ַ�����
 * 
 * @param string �ַ�������
 * @return char ���������ַ�
 */
static char shellExtParseChar(char *string)
{
    char *p = (*string == '\'') ? (string + 1) : string;
    char value = 0;

    if (*p == '\\')
    {
        switch (*(p + 1))
        {
        case 'b':
            value = '\b';
            break;
        case 'r':
            value = '\r';
            break;
        case 'n':
            value = '\n';
            break;
        case 't':
            value = '\t';
            break;
        case '0':
            value = 0;
            break;
        default:
            value = *(p + 1);
            break;
        }
    }
    else
    {
        value = *p;
    }
    return value;
}


/**
 * @brief �����ַ�������
 * 
 * @param string �ַ�������
 * @return char* ���������ַ���
 */
static char* shellExtParseString(char *string)
{
    char *p = string;
    unsigned short index = 0;

    if (*string == '\"')
    {
        p = ++string;
    }

    while (*p)
    {
        if (*p == '\\')
        {
            *(string + index) = shellExtParseChar(p - 1);
            p++;
        }
        else if (*p == '\"')
        {
            *(string + index) = 0;
        }
        else
        {
            *(string + index) = *p;
        }
        p++;
        index ++;
    }
    *(string + index) = 0;
    return string;
}


/**
 * @brief �������ֲ���
 * 
 * @param string �ַ�������
 * @return unsigned int ������������
 */
static unsigned int shellExtParseNumber(char *string)
{
    ShellNumType type = NUM_TYPE_DEC;
    char radix = 10;
    char *p = string;
    char offset = 0;
    signed char sign = 1;
    unsigned int valueInt = 0;
    unsigned int valueFloat = 0.0;
    unsigned int devide = 0;

    if (*string == '-')
    {
        sign = -1;
    }

    type = shellExtNumType(string + ((sign == -1) ? 1 : 0));

    switch ((char)type)
    {
    case NUM_TYPE_HEX:
        radix = 16;
        offset = 2;
        break;
    
    case NUM_TYPE_OCT:
        radix = 8;
        offset = 1;
        break;

    case NUM_TYPE_BIN:
        radix = 2;
        offset = 2;
        break;
    
    default:
        break;
    }

    p = string + offset + ((sign == -1) ? 1 : 0);

    while (*p)
    {
        if (*p == '.')
        {
            devide = 1;
            p++;
            continue;
        }
        valueInt = valueInt * radix + shellExtToNum(*p);
        devide *= 10;
        p++;
    }
    if (type == NUM_TYPE_FLOAT && devide != 0)
    {
        valueFloat = (valueInt * sign) / devide;
        return valueFloat;
    }
    else
    {
        return valueInt * sign;
    }
}


/**
 * @brief ������������
 * 
 * @param shell shell����
 * @param var ����
 * @return unsigned int ����ֵ
 */
static unsigned int shellExtParseVar(Shell *shell, char *var)
{
    ShellCommand *command = shellSeekCommand(shell,
                                             var + 1,
                                             shell->commandList.base,
                                             0);
    if (command)
    {
        return shellGetVarValue(shell, command);
    }
    else
    {
        return 0;
    }
}


/**
 * @brief ��������
 * 
 * @param shell shell����
 * @param string ����
 * @param result �������
 * 
 * @return int 0 �����ɹ� --1 ����ʧ��
 */
int shellExtParsePara(Shell *shell, char *string, char *type, unsigned int *result)
{
    if (type == NULL || (*string == '$' && *(string + 1)))
    {
        if (*string == '\'' && *(string + 1))
        {
            *result = (unsigned int)shellExtParseChar(string);
            return 0;
        }
        else if (*string == '-' || (*string >= '0' && *string <= '9'))
        {
            *result = (unsigned int)shellExtParseNumber(string);
            return 0;
        }
        else if (*string == '$' && *(string + 1))
        {
            *result = shellExtParseVar(shell, string);
            return 0;
        }
        else if (*string)
        {
            *result = (unsigned int)shellExtParseString(string);
            return 0;
        }
    }
#if SHELL_USING_FUNC_SIGNATURE == 1
    else
    {
        if (strcmp("c", type) == 0)
        {
            *result = (unsigned int)shellExtParseChar(string);
            return 0;
        }
        else if (strcmp("i", type) == 0
                 || strcmp("f", type) == 0
                 || strcmp("p", type) == 0)
        {
            *result = (unsigned int)shellExtParseNumber(string);
            return 0;
        }
        else if (strcmp("s", type) == 0)
        {
            *result = (unsigned int)shellExtParseString(string);
            return 0;
        }
        else
        {
            ShellCommand *command = shellSeekCommand(shell,
                                                     type,
                                                     shell->commandList.base,
                                                     0);
            if (command != NULL)
            {
                void *param;
                if (command->data.paramParser.parser(shellExtParseString(string), &param) == 0)
                {
                    *result = (unsigned int)param;
                    return 0;
                }
                else
                {
                    shellWriteString(shell, "Parse param for type: ");
                    shellWriteString(shell, type);
                    shellWriteString(shell, " failed\r\n");
                    return -1;
                }
            }
            else
            {
                shellWriteString(shell, "Can't find the param parser for type: ");
                shellWriteString(shell, type);
                shellWriteString(shell, "\r\n");
                return -1;
            }
        }
    }
#endif /** SHELL_USING_FUNC_SIGNATURE == 1 */
    return -1;
}


#if SHELL_USING_FUNC_SIGNATURE == 1
int shellExtCleanerPara(Shell *shell, char *type, unsigned int param)
{
    if (type == NULL)
    {
        return 0;
    }
    else
    {
        if (strcmp("c", type) == 0
            || strcmp("i", type) == 0
            || strcmp("f", type) == 0
            || strcmp("p", type) == 0
            || strcmp("s", type) == 0)
        {
            return 0;
        }
        else
        {
            ShellCommand *command = shellSeekCommand(shell,
                                                     type,
                                                     shell->commandList.base,
                                                     0);
            if (command != NULL && command->data.paramParser.cleaner != NULL)
            {
                return command->data.paramParser.cleaner((void *)param);
            }
        }
    }
    return -1;
}
#endif /** SHELL_USING_FUNC_SIGNATURE == 1 */


/**
 * @brief ִ������
 * 
 * @param shell shell����
 * @param command ����
 * @param argc ��������
 * @param argv ����
 * @return int ����ֵ
 */
int shellExtRun(Shell *shell, ShellCommand *command, int argc, char *argv[])
{
    int ret = 0;
    unsigned int params[SHELL_PARAMETER_MAX_NUMBER] = {0};
    int paramNum = command->attr.attrs.paramNum > (argc - 1) ? 
        command->attr.attrs.paramNum : (argc - 1);
#if SHELL_USING_FUNC_SIGNATURE == 1
    char type[16];
    int index = 0;
    
    if (command->data.cmd.signature != NULL)
    {
        int except = shellGetParamNumExcept(command->data.cmd.signature);
        if (except != argc - 1)
        {
            shellWriteString(shell, "Parameters number incorrect\r\n");
            return -1;
        }
    }
#endif
    for (int i = 0; i < argc - 1; i++)
    {
    #if SHELL_USING_FUNC_SIGNATURE == 1
        if (command->data.cmd.signature != NULL) {
            index = shellGetNextParamType(command->data.cmd.signature, index, type);
            if (shellExtParsePara(shell, argv[i + 1], type, &params[i]) != 0)
            {
                return -1;
            }
        }
        else
    #endif /** SHELL_USING_FUNC_SIGNATURE == 1 */
        {
            if (shellExtParsePara(shell, argv[i + 1], NULL, &params[i]) != 0)
            {
                return -1;
            }
        }
    }
    switch (paramNum)
    {
#if SHELL_PARAMETER_MAX_NUMBER >= 1
    case 0:
        ret = command->data.cmd.function();
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 1 */
#if SHELL_PARAMETER_MAX_NUMBER >= 2
    case 1:
        ret = command->data.cmd.function(params[0]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 2 */
#if SHELL_PARAMETER_MAX_NUMBER >= 3
    case 2:
        ret = command->data.cmd.function(params[0], params[1]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 3 */
#if SHELL_PARAMETER_MAX_NUMBER >= 4
    case 3:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 4 */
#if SHELL_PARAMETER_MAX_NUMBER >= 5
    case 4:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 5 */
#if SHELL_PARAMETER_MAX_NUMBER >= 6
    case 5:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 6 */
#if SHELL_PARAMETER_MAX_NUMBER >= 7
    case 6:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 7 */
#if SHELL_PARAMETER_MAX_NUMBER >= 8
    case 7:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 8 */
#if SHELL_PARAMETER_MAX_NUMBER >= 9
    case 8:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 9 */
#if SHELL_PARAMETER_MAX_NUMBER >= 10
    case 9:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7],
                                          params[8]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 10 */
#if SHELL_PARAMETER_MAX_NUMBER >= 11
    case 10:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7],
                                          params[8], params[9]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 11 */
#if SHELL_PARAMETER_MAX_NUMBER >= 12
    case 11:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7],
                                          params[8], params[9],
                                          params[10]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 12 */
#if SHELL_PARAMETER_MAX_NUMBER >= 13
    case 12:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7],
                                          params[8], params[9],
                                          params[10], params[11]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 13 */
#if SHELL_PARAMETER_MAX_NUMBER >= 14
    case 13:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7],
                                          params[8], params[9],
                                          params[10], params[11],
                                          params[12]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 14 */
#if SHELL_PARAMETER_MAX_NUMBER >= 15
    case 14:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7],
                                          params[8], params[9],
                                          params[10], params[11],
                                          params[12], params[13]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 15 */
#if SHELL_PARAMETER_MAX_NUMBER >= 16
    case 15:
        ret = command->data.cmd.function(params[0], params[1],
                                          params[2], params[3],
                                          params[4], params[5],
                                          params[6], params[7],
                                          params[8], params[9],
                                          params[10], params[11],
                                          params[12], params[13],
                                          params[14]);
        break;
#endif /** SHELL_PARAMETER_MAX_NUMBER >= 16 */
    default:
        ret = -1;
        break;
    }
    
#if SHELL_USING_FUNC_SIGNATURE == 1
    if (command->data.cmd.signature != NULL) {
        index = 0;
        for (int i = 0; i < argc - 1; i++)
        {
            index = shellGetNextParamType(command->data.cmd.signature, index, type);
            shellExtCleanerPara(shell, type, params[i]);
        }
    }
#endif /** SHELL_USING_FUNC_SIGNATURE == 1 */

    return ret;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __HIGHTEC__
#pragma GCC diagnostic pop
#endif

#ifdef __ghs__
#pragma ghs endnowarning 1518
#endif
