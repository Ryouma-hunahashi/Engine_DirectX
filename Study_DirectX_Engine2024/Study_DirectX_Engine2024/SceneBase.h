#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <typeindex>
#include <functional>


// �I�u�W�F�N�g�v�[���̎���
// ���������蓖�Ă��œK�����A�I�u�W�F�N�g�̍ė��p���\�ɂ���
template<typename T>
class ObjectPool {
private:
    std::vector<std::unique_ptr<T>> objects;
    std::vector<T*> freeList;

public:
    // �I�u�W�F�N�g���擾����i�V�K�쐬�܂��͍ė��p�j
    T* Acquire() {
        if (freeList.empty()) {
            objects.push_back(std::make_unique<T>());
            return objects.back().get();
        }
        T* obj = freeList.back();
        freeList.pop_back();
        return obj;
    }

    // �I�u�W�F�N�g��������A�ė��p�\�ɂ���
    void Release(T* obj) {
        freeList.push_back(obj);
    }
};

// �V�[���I�u�W�F�N�g�̊��N���X
class SceneObjectBase {
public:
    virtual ~SceneObjectBase() = default;
};

// �^���S�ȃV�[���I�u�W�F�N�g�̃N���X
template<class T>
class SceneObject : public SceneObjectBase {
public:
    SceneObject(std::unique_ptr<T> ptr) : m_pObj(std::move(ptr)) {}
    T* Get() { return m_pObj.get(); }

private:
    std::unique_ptr<T> m_pObj;
};

/// <summary>
/// Scene���N���X
/// </summary>
class SceneBase
{
private:

    // �I�u�W�F�N�g�Ƃ��̖��O���i�[����}�b�v���쐬���Ă���
    using Objects = std::unordered_map<std::string, std::unique_ptr<SceneObjectBase>>;
    using Items = std::vector<std::string>;


public:
    // �R���X�g���N�^�ƃf�X�g���N�^
    SceneBase() = default;
    virtual ~SceneBase() = default;
    // �V�[���̏���������
    virtual void Initialize() = 0;
    // �V�[���̍X�V����
    virtual void Update(float _deltaTime) = 0;
    // �V�[���̕`�揈��
    virtual void Draw() = 0;
    // �V�[���̏I������
    virtual void Finalize() = 0;
    // �T�u�V�[���̒ǉ�
    template<class T>
    T* AddSubScene();
    // �T�u�V�[���̍폜
    void RemoveSubScene();

    // �I�u�W�F�N�g�̐���
    template<class T>
    T* CreateObj(const char* name);
    // �I�u�W�F�N�g�̔j��
    void DestroyObj(const char* name);
    // �I�u�W�F�N�g�̎擾
    template<class T>
    T* GetObj(const char* name);
private:
    static Objects m_objects;
    // �I�u�W�F�N�g�����p�t�@�N�g���[�֐��̃}�b�v
    static std::unordered_map<std::string, std::function<std::unique_ptr<SceneObjectBase>()>> m_factories;

protected:
    SceneBase* m_pParent = nullptr;
    std::unique_ptr<SceneBase> m_pSubScene;
    Items m_items;

    // �I�u�W�F�N�g�����p�t�@�N�g���[�֐��̓o�^
    template<class T>
    static void RegisterFactory() {
        std::string typeName = typeid(T).name();
        m_factories[typeName] = []() { return std::make_unique<SceneObject<T>>(std::make_unique<T>()); };
    }
};

// �T�u�V�[���̒ǉ�
template<class T>
T* SceneBase::AddSubScene() {
    m_pSubScene = std::make_unique<T>();
    m_pSubScene->m_pParent = this;
    m_pSubScene->Initialize();
    return static_cast<T*>(m_pSubScene.get());
}

// �I�u�W�F�N�g�̐���
template<class T>
T* SceneBase::CreateObj(const char* name) {
    std::string typeName = typeid(T).name();
    auto it = m_factories.find(typeName);
    if (it == m_factories.end()) {
        // �t�@�N�g���[�����o�^�̏ꍇ�A�o�^����
        RegisterFactory<T>();
        it = m_factories.find(typeName);
    }

    // �I�u�W�F�N�g�̐����Ɠo�^
    auto obj = it->second();
    auto* pObj = static_cast<SceneObject<T>*>(obj.get())->Get();
    m_objects[name] = std::move(obj);
    m_items.push_back(name);
    return pObj;
}

// �I�u�W�F�N�g�̎擾
template<class T>
T* SceneBase::GetObj(const char* name) {
    auto it = m_objects.find(name);
    if (it == m_objects.end()) return nullptr;
    return static_cast<SceneObject<T>*>(it->second.get())->Get();
}

