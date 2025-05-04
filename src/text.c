#include "planet_guardian.h"

void printp(char *msg, float x, float y, float size, Color color)
{
    DrawTextEx(game.font, msg, (Vector2){x, y}, size * (float)game.font.baseSize, 1.0f, color);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	joined_len;
	char	*joined;
	size_t	joined_i;
	size_t	s_i;

	if (!s1 || !s2)
		return (NULL);
	joined_len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(joined_len + 1);
	if (joined == NULL)
		return (NULL);
	joined_i = 0;
	s_i = 0;
	while (s1[s_i])
		joined[joined_i++] = s1[s_i++];
	s_i = 0;
	while (s2[s_i])
		joined[joined_i++] = s2[s_i++];
	joined[joined_i] = 0;
	return (joined);
}
