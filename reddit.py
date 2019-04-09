import praw  # Python Reddit API Wrapper
from nltk.tokenize import word_tokenize  # tool to get each word in a sentence/phrase

reddit = praw.Reddit(client_id='Tu5oWsGc7cnafw',
                     client_secret='hjRwgAylwvkcGjxJWyPAT-eYIhI',
                     username='DankulousMemeLord',
                     password='Blue12House$',
                     user_agent='memes')  # logging into reddit

print('Logged into Reddit')
subreddit = reddit.subreddit('Memes_Of_The_Dank')  # specify which subreddit to read from

hot = subreddit.hot(limit=5)  # get memes from new

file = open("memes.txt", "w")


def repost_check(comment):
    for i in word_tokenize(comment):
        word = i.lower()
        if word == 're' or word == 'ree' or word == 'reee' or word == 'reeee':
            print('flagged word: ', word)
            return True
        if word == 'repost':
            print('flagged word: ', word)
            return True

    return False


for submission in hot:
    if not submission.stickied:
        title = submission.title
        print(title)
        url = submission.url
        # print('URL: ', url)
        upVotes = submission.ups
        # print('up votes: ', upVotes)
        time = submission.created_utc
        # print('time: ', time, '\n')
        comments = submission.comments.list()
        repost = False
        print('Checking comments for signs of a repost...')
        for comment in comments:
            repost = repost_check(comment.body)
            if repost:
                print('REPOST')
                break

        if repost is None:
            print('Error reading boolean', '\n', '\n')
        elif not repost:
            print('Writing to file...', '\n', '\n')
            file.write(title)
            file.write('\n')
            file.write(url)
            file.write('\n')
            file.write(str(upVotes))
            file.write('\n')
            file.write(str(time))
            file.write('\n')
        else:
            print('Do not write post (repost)', '\n')

file.close()
