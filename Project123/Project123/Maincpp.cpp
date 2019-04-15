

int main()
{

	for (i = 0; i&lt; n - 1; i++)
	{
		for (j = i + 1; j&lt; n; j++) {
			&nbsp;   if (num[i] & gt; num[j]) {
				var = num[i];
				num[i] = num[j];
				num[j] = var;
			}
		}
	}
	return 0;
}