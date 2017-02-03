from . import cfg
from PyQt5.QtWidgets import QListWidget

#
# def test_close_database(qtbot, data_object):
#     assert len(data_object.database_manager.database_for_int_dict) == 1
#
#
# def test_close_and_load_the_same_database(qtbot, data_object):
#
#     # window = QListWidget()
#     # window.show()
#     # qtbot.addWidget(window)
#     print("test_close_and_load_the_same_database")
#     print(data_object.database_manager.database_for_int_dict.keys())
#     # closing already opened project :
#     with qtbot.waitSignal(data_object.signal_hub.item_value_returned, timeout=1000) as blocker:
#         data_object.project_hub.close_project(0)
#     project_id, paper_id, type, value = blocker.args
#     assert blocker.signal_triggered
#     assert project_id == 0
#
#     # window.clear()
#     # window.addItems(cfg.data.task_manager._task_list)
#
#     # loading new project :
#     with qtbot.waitSignal(cfg.data.signal_hub.item_value_returned, timeout=1000) as blocker:
#         cfg.data.project_hub.load_project(cfg.test_database_path)
#     project_id, paper_id, type, value = blocker.args
#     print(data_object.database_manager.database_for_int_dict.keys())
#
#     assert blocker.signal_triggered
#     assert project_id == 1


def test_lastProjectLoaded(qtbot, data_object):
    last_loaded = data_object.projectHub().getLastLoaded()
    assert last_loaded != 0

def test_loadProject_like(qtbot, data_object):
    project_id = data_object.projectHub().getLastLoaded()
    print(str(project_id))
    assert project_id != 0
    print("2")
    write_hub = data_object.writeHub()
    _title = write_hub.getTitle(project_id, 1)
    print("3")
    _title_dict = write_hub.getAllTitles(project_id)
    print("4")
    _id_list = write_hub.getAllIds(project_id)
    print("5")
    _indent_dict = write_hub.getAllIndents(project_id)
    _sort_order_dict = write_hub.getAllSortOrders(project_id)
    assert len(_id_list) > 0
    assert len(_title_dict) > 0
    assert len(_indent_dict) > 0
    assert len(_sort_order_dict) > 0

