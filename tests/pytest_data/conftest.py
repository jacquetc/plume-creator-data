import pytest
import sys
from . import cfg
from PyQt5.QtCore import QCoreApplication
import os




@pytest.fixture(scope="function", autouse=True)
def my_own_class_run_at_beginning(request):
    print('\nOpening')
    cfg.app = QCoreApplication.instance()


    def my_own_class_run_at_end():
        print('Closing')


    request.addfinalizer(my_own_class_run_at_end)


def test_tasks_run_false(status):
    """Return true if tasks_run signal is False."""
    return status == False


@pytest.fixture()
def data_object(request, qtbot):

    _df = os.environ.get('PLUME_DEVELOP_DATA_BUILD_FROM', None)
    if _df and os.path.exists(_df):
        sys.path.insert(0, _df)
        from ctypes import cdll
        cdll.LoadLibrary(_df + "/libplume-creator-data.so.1.61")

    import plmdata

    print('[setup] Data')
    # code to connect to your db
    cfg.data = plmdata.PLMData(cfg.app)
    with qtbot.waitSignal(cfg.data.projectHub().projectLoaded, timeout=1000) as blocker:
        cfg.data.projectHub().loadProject(cfg.test_database_path)

    def end():
        print('\n[teardown] Data')
        id_list = cfg.data.projectHub().getProjectIdList()
        print("project list :" + repr(id_list))

        if not id_list:
            print("no project listed")
            return
        with qtbot.waitSignal(cfg.data.projectHub().projectClosed, timeout=1000) as blocker:
            cfg.data.projectHub().closeProject(id_list[-1])

    request.addfinalizer(end)

    return cfg.data
