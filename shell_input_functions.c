#include "shell_master.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @commandBuffer: address of command buffer
 * @bufferLength: address of buffer length var
 * Return: bytes read.
 **/
ssize_t input_buf(info_t *info, char **commandBuffer, size_t *bufferLength)
{
	ssize_t bytesRead = 0;
	size_t currentBufferLength = 0;

	if (!*bufferLength)
	{
		free(*commandBuffer);
		*commandBuffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytesRead = getline(commandBuffer, &currentBufferLength, stdin);
#else
		bytesRead = _getline(info, commandBuffer, &currentBufferLength);
#endif
		if (bytesRead > 0)
		{
			if ((*commandBuffer)[bytesRead - 1] == '\n')
			{
				(*commandBuffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->linecountFlag = 1;
			remove_comments(*commandBuffer);
			build_history_list(info, *commandBuffer, info->histcount++);
			if (_strchr(*commandBuffer, ';'))
			{
				*bufferLength = bytesRead;
				info->cmdBuffer = commandBuffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read.
 **/
ssize_t get_input(info_t *info)
{
	static char *inputBuffer;
	static size_t bufferIndex, nextIndex, bufferLength;
	ssize_t bytesRead = 0;
	char **currentBuffer = &(info->arg), *currentChar;

	_putchar(BUF_FLUSH);
	bytesRead = input_buf(info, &inputBuffer, &bufferLength);

	if (bytesRead == -1)
		return (-1);

	if (bufferLength)
	{
		nextIndex = bufferIndex;
		currentChar = inputBuffer + bufferIndex;
		check_chain(info, inputBuffer, &nextIndex, bufferIndex, bufferLength);

		while (nextIndex < bufferLength)
		{
			if (is_chain(info, inputBuffer, &nextIndex))
				break;
			nextIndex++;
		}
		bufferIndex = nextIndex + 1;

		if (bufferIndex >= bufferLength)
		{
			bufferIndex = bufferLength = 0;
			info->cmdBufferType = CMD_NORM;
		}
		*currentBuffer = currentChar;
		return (_strlen(currentChar));
	}
	*currentBuffer = inputBuffer;
	return (bytesRead);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @index: size
 * Return: bytesRead
 **/
ssize_t read_buf(info_t *info, char *buffer, size_t *index)
{
	ssize_t bytesRead = 0;

	if (*index)
		return (0);
	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*index = bytesRead;
	return (bytesRead);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: totalBytesRead
 **/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char readBuffer[READ_BUF_SIZE];
	size_t bytesRead, readBufferIndex;
	ssize_t totalBytesRead = 0;
	char *currentPtr = NULL, *newPtr = NULL, *currentChar;

	currentPtr = *ptr;
	if (currentPtr && length)
		totalBytesRead = *length;
	if (bufferIndex == bufferLength)
		bufferIndex = bufferLength = 0;
	bytesRead = read_buf(info, readBuffer, &bufferLength);
	if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
		return (-1);
	currentChar = _strchr(readBuffer + bufferIndex, '\n');
	readBufferIndex = currentChar ? 1 + (unsigned int
			(currentChar - readBuffer) : bufferLength;
	newPtr = _realloc(currentPtr, totalBytesRead, totalBytesRead ? totalBytesRead
			+ readBufferIndex : readBufferIndex + 1);
	if (!newPtr)
		return (currentPtr ? (free(currentPtr), -1) : -1);
	if (totalBytesRead)
		_strncat(newPtr, readBuffer + bufferIndex, readBufferIndex - bufferIndex);
	else
		_strncpy(newPtr, readBuffer + bufferIndex,
				readBufferIndex - bufferIndex + 1);
	totalBytesRead += readBufferIndex - bufferIndex;
	bufferIndex = readBufferIndex;
	currentPtr = newPtr;
	if (length)
		*length = totalBytesRead;
	*ptr = currentPtr;
	return (totalBytesRead);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sigNum: the signal number
 * Return: void
 **/
void sigintHandler(__attribute__((unused)) int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


