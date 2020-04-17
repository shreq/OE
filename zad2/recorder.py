from pymoo.model.callback import Callback
from pymoo.visualization.pcp import PCP
from pyrecorder.recorders.streamer import Streamer
from pyrecorder.video import Video


class RecorderCallback(Callback):
    video = None

    def __init__(self):
        super().__init__()
        self.video = Video(Streamer())

    def notify(self, algorithm):
        problem = algorithm.problem

        pcp = PCP(
            title=(
                'Gen %s' % algorithm.n_gen,
                {'pad': 30}
            ),
            bounds=(
                problem.xl,
                problem.xu
            ),
            labels=['$x_%s$' % i for i in range(problem.n_var)]
        )
        pcp.set_axis_style(
            color='grey',
            alpha=0.1
        )
        # pcp.add(
        #     algorithm.pop.get('X'),
        #     color='black',
        #     alpha=0.8,
        #     linewidth=1.5
        # )

        # try:
        #     pcp.add(
        #         algorithm.off.get('X'),
        #         color='blue',
        #         alpha=0.8,
        #         linewidth=0.5
        #     )
        # except AttributeError:
        #     pass

        pcp.add(
            algorithm.opt.get('X'),
            color='red',
            linewidth=1
        )
        pcp.do()

        self.video.record()
