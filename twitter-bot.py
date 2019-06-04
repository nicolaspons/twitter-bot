import tweepy

consumer_token = "yEGJYmBjw6lELpxfmYT3uqUQd"
consumer_secret = "jtv6R7kjzdG6ghYMepxgGC1k69ZGU02W3TmPUqn5wIEK8eqZkD"

access_key = "1135834249498697728-9ST3L0x3RvLzU9H8h9Inm04lnUnCE3"
access_secret = "fkIUjLP5uqBmcdo8nZEVQIBi07wOjn8BWF4Px6wgFlL3n"

auth = tweepy.OAuthHandler(consumer_token, consumer_secret)
auth.set_access_token(access_key, access_secret)
api = tweepy.API(auth)

api.update_status('#HelloWorld')