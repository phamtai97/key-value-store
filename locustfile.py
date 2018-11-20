from locust import HttpLocust, TaskSet


class UserBehavior(TaskSet):
    def on_start(self):
        """ on_start is called when a Locust start before any task is scheduled """
        print("start")

    def on_stop(self):
        """ on_stop is called when the TaskSet is stopping """
        print("stop")


class WebsiteUser(HttpLocust):
    task_set = UserBehavior
    min_wait = 5000
    max_wait = 9000
